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

#include "sre_base.h"
#include "sre_sys.h"
#include "sre_task.h"
#include "iCunit.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#define CACHE_MEM_SIZE            (OS_CACHE_LINE_SIZE*4)        /*申请测试内存大小*/
#define CACHE_TEST_SIZE           (OS_CACHE_LINE_SIZE*2)        /*实际测试内存大小*/
#define CACHE_MIN_SIZE            64                            /*Cache 的最小颗粒*/
#define CACHE_LOOP_CNT            (CACHE_TEST_SIZE/CACHE_MIN_SIZE) /*实际测试区域包含多少个最小颗粒*/

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
    UINT32 uwAddr;          /* 出错的地址   */
    UINT32 uwCheckVal;      /* 比对的值     */
    UINT32 uwReadVal;       /* 读取到的值   */
    UINT32 uwStep;          /* 阶段数       */
}CACHE_REC_ST;

typedef struct tagOsTestRec
{
    CACHE_REC_ST stCacheTestRec;    /* cache测试结果记录    */
}OSTESC_REC_ST;

typedef enum
{
    CACHE_NOT_WB = 1,   /* cache上的数据为测试数据，内存里面的数据为0xdd */
    CACHE_WB            /* cache上的数据与内存里的数据一致 */
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



/* cache测试区的大小 */
#define CACHE_BUFFER            0x8000   /*32K*/

/* cache 测试大小 */
#define CACHE_TEST_SIZE_0       0x8000
#define CAHCE_TEST_SIZE_1       0xFFFFFFFF

/* cahce测试的写入值 */
#define CACHE_TEST_VALUE        0xdd
#define CACHE_TEST_VALUE1        0x5A


#if (OS_HARDWARE_PLATFORM == OS_SC3400)
#pragma section ".CACHE_TEST_DATA"  kind data

/* cache测试缓冲区 */
UINT8 g_acTestBuf[CACHE_BUFFER] = {1,1,1};
#pragma place g_acTestBuf ".CACHE_TEST_DATA"
#pragma align g_acTestBuf 32768
#endif

volatile UINT32 g_uwICacheTestGuard;


/* cache 测试时全部用全局变量 */
UINT32 g_uwIndex;
UINT8  g_ucTestData;
UINT32 g_uwNewFuncFlag = 0;

OSTESC_REC_ST g_stTestRec;


//#if (OS_HARDWARE_PLATFORM == OS_XTENSA2)
#if (OS_HARDWARE_PLATFORM == OS_CORTEX_A9)

//__attribute__((section(".shared.cache.data")))
UINT8 g_acTestBuf[CACHE_BUFFER] ;/* 共享动态Pool内存单元测试使用分区   */
//UT_TEST   UT所需变量定义


UINT32 UT_CacheFun(UINT32 uwValue, UINT32 uwSize)
{
    UINT8 *puwAddr;
    UINTPTR uwSave = 0;
    /* 关闭中断 */
    uwSave = SRE_IntLock();

    /* 先无效*/
    SRE_DCacheInv((VOID *)&g_acTestBuf[0], uwSize, 1);

    /* 将0xdd写入内存中 */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
    }

    /* write 0x55 ro RAM */
    puwAddr = (UINT8*)&g_acTestBuf[0] + 0x80000000;
    memset((UINT8*)puwAddr,CACHE_TEST_VALUE1,uwSize);

    /* 无效*/
    SRE_DCacheInv((VOID *)&g_acTestBuf[0], uwSize, 1);

    /* 从TestBuf中读数据，数据应该写入 */
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


    /* 将0xdd写入内存中 */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
    }

    SRE_DCacheFlush((VOID *)&g_acTestBuf[0], uwSize, 1);

    /* test SRE_DCacheFlushInv 和地址双映射*/
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


    /* 将CACHE_TEST_VALUE1写入内存中 */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE1;
    }

    SRE_DCacheFlushInv((VOID *)&g_acTestBuf[0], uwSize, 1);

    /* test cacheWb 和地址双映射*/
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
    /* 打开中断 */
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
    /* 关闭中断 */
    UINTPTR uwSave;
    uwSave = SRE_IntLock();

    /* 关闭cache */
    uniDCacheDisable();

    /* 将0xdd写入内存中 */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
    }

    /* 打开cache */
    uniDCacheEnable();

    /* 先无效g_acTestBuf对应的cache空间 */
    SRE_DCacheInv((VOID *)&g_acTestBuf, uwSize, 1);

    /* 将内存映射到g_acTestBuf的cache中 */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_ucTestData = g_acTestBuf[g_uwIndex];
    }

    /* 测试数据全部写到cache上，不同步到memory */
    g_ucTestData = uwValue;
    for (g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = g_ucTestData;
    }

    uniDCacheDisable();

    /* 从TestBuf中读数据，数据应该写入 */
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
    /* 打开中断 */
    (VOID)SRE_IntRestore(uwSave);
    return ICUNIT_SUCCESS;
}
#endif

UINT32 UT_MutiCoreTest(UINT32 uwData, UINT32 uwLen)
{
    UINT32 uwRet = ICUNIT_SUCCESS;

#if (OS_HARDWARE_PLATFORM == OS_SC3400)/* tensilica 下先暂时不测多核*/
    uniWaitForAllCores();
    if(0 == SRE_GetCoreID())
#endif
    {
        uwRet = UT_CacheFun(uwData, uwLen);
        ICUNIT_ASSERT_EQUAL(uwRet, ICUNIT_SUCCESS, uwRet);
    }

/** 对于Tensilica 平台，暂时测试单核*/
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
*-@tspec cache数据测试，测试长度32k，测试数据0x00
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
*-@tspec cache数据测试，测试长度32k，测试数据0xff
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
*-@tspec cache数据测试，测试长度32k，测试数据0x55
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
*-@tspec cache数据测试，测试长度32k，测试数据0xaa
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
*-@tspec cache数据测试，测试长度32k，测试数据0x33
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
*-@tspec cache数据测试，测试长度32k，测试数据0xcc
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
*-@tspec cache数据测试，测试长度32k，测试数据0xf0
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
*-@tspec cache数据测试，测试长度32k，测试数据0x0f
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

#if (OS_HARDWARE_PLATFORM == OS_SC3400)/* tensilica 下先暂时不测多核*/
/**
*@test UT_uniCacheData_009
*-@tspec cache数据测试，测试长度整个cache line，测试数据0x55
*-@ttitle
*-@tbrief
*-#关闭cache，由主核将0xdd写入内存，然后打开cache，主核将0x55写入cache中，
*-#从核读取数据为0xdd，主核为0x55，主核回写所有cache，从核读取的数据为0x55
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_009(VOID)
{
     //UINT32 uwRet = OS_FAIL;原来的用例，这里逻辑有点问题。
    UINT32 uwRet = ICUNIT_SUCCESS;
    UINTPTR uwSave = 0;
    /* 关闭中断 */
    uwSave = SRE_IntLock();

    /* 关闭cache */
    uniDCacheDisable();

    uniWaitForAllCores();
    if(0 == SRE_GetCoreID())
    {
        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
        }
    }
    /* 打开cache */
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

    /* 打开中断 */
    (VOID)SRE_IntRestore(uwSave);
    return uwRet;
}

/**
*@test UTest_uniCacheData_010
*-@tspec cache数据测试，测试长度256字节，测试数据0x55
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_010(VOID)
{
    //UINT32 uwRet = OS_FAIL;原来的用例，这里逻辑有点问题。
    UINT32 uwRet = ICUNIT_SUCCESS;
    UINT32 uwTestSize = 256;
    UINTPTR uwSave = 0;

    if(0 == SRE_GetCoreID())
    {
        /* 关闭中断 */
        uwSave = SRE_IntLock();

        /* 关闭cache */
        uniDCacheDisable();

        /* 内存中的数据先全部写为0xdd */
        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
        }

        /* 打开cache */
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

        /* 打开中断 */
        SRE_IntRestore(uwSave);
    }

    return uwRet;
}

/**
*@test UTest_uniCacheData_011
*-@tspec cache数据测试，测试长度128字节，测试数据0x55
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_011(VOID)
{
     //UINT32 uwRet = OS_FAIL;原来的用例，这里逻辑有点问题。
    UINT32 uwRet = ICUNIT_SUCCESS;
    UINT32 uwTestSize = 256;
    UINTPTR uwSave = 0;


    if(0 == SRE_GetCoreID())
    {
        /* 关闭中断 */
        uwSave = SRE_IntLock();

        /* 关闭cache */
        uniDCacheDisable();

        /* 内存中的数据先全部写为0xdd */
        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
        }

        /* 打开cache */
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

        /* 打开中断 */
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
*-@tspec cache使能禁止测试
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
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
*-@tspec cache数据测试
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
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
*-@tspec cache数据测试
*-@ttitle
*-@tbrief 回写无效SRE_DCacheFlushInv
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
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
*-@tspec cache数据测试
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
    }
    SRE_DCacheFlushAll();              //无效之前先刷入所有
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
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
*-@tspec cache数据测试
*-@ttitle
*-@tbrief 禁止使能后操作cache后无效之，最后恢复使能,再操作cache再无效之，最后正常flush
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
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
        auwTest[uwLoop] = 0;  //赋值
    }
    SRE_DCacheFlush(auwTest, 80, TRUE); //刷入赋值操作
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM; //操作cache备份
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
        uwTemp = auwTest[uwLoop];  // 载入cache
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
*-@tspec cache数据测试
*-@ttitle
*-@tbrief 禁止使能后操作cache后无效之，最后恢复使能,再操作cache再无效之，最后flushALL
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
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
        auwTest[uwLoop] = 0;  //赋值
    }
    SRE_DCacheFlush(auwTest, 80, TRUE); //刷入赋值操作
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM; //操作cache备份
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
        uwTemp = auwTest[uwLoop];  // 载入cache
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
*-@tspec cache数据测试
*-@ttitle
*-@tbrief 先操作断言，再无效断言
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
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
        uwTemp = auwTest[uwLoop];  // 载入cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // 操作Cache中的备份
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


#if (OS_HARDWARE_PLATFORM == OS_SC3400)/* tensilica 下先暂时不测多核*/
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
