/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : ut_uni_cachemmu.c
* Description :
* Platform    :
* Author      :
* Version     : 1.0
* Date        :
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date         Author          Modifications
    2013-04-18   h006996       created
*******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/


#include "sre_base.h"
#include "sre_sys.h"
#include "sre_hwi.ph"
#include "sre_hwi.h"
#include "secure_gic_init.h"
#include "iCunit.h"
#include "sre_securecpu.h"
#include "sre_securecache.h"
#include "sre_securemmu.h"
#include "boot.h"

//#define TEST_CACHE_DEBUG

#define CACHE_BUFFER_SIZE            0x200 //512

#define CACHE_TEST_VALUE 0x1234DDDD
#define CACHE_TEST_VALUE1 0xA5A5A5A5
#define CACHE_TEST_NUM 20
#define CACHE_TEST_SIZE (CACHE_TEST_NUM*4)


UINT32 g_acTestBuf[CACHE_BUFFER_SIZE] = {1,1,1};
UINT32 g_memBackup[CACHE_TEST_SIZE];

extern UINT32 secure_page_table[PAGE_TABLE_ENTRIES];
extern void uart_printf_func(const char *fmt, ...);

#if 0
static UINT32 read_CCSIDR(void) {
    UINT32 rval;
    __asm__ __volatile__ (
                         "mrc     p15, 1, %0, c0, c0, 0"
                         :"=r"(rval));
    return rval;
}


static UINT32 read_ACTLR(void) {
    UINT32 rval;
    __asm__ __volatile__ (
                         "mrc     p15, 0, %0, c1, c0, 1"
                         :"=r"(rval));
    return rval;
}

static UINT32 UT_cache_info()
{
    UINT32 rval;
    rval = read_CCSIDR();
    uart_printf("read_CCSIDR=%x\n", rval);

    rval = read_ACTLR();
    uart_printf("read_ACTLR=%x\n", rval);

    return SRE_OK;
}
#endif

/*dcache_enable_disable*/
static UINT32 UT_SRE_CACHE_001()
{
    UINT32 uwRet = OS_FAIL;
    UINTPTR uwSave = 0;
    UINT32 temp;
    //disable interrupt
    uwSave = __SRE_IntLock();

    SRE_DCacheDisable();
    temp = read_sctlr();
    if ((temp & SCTLR_C))
        goto EXIT;

    SRE_DCacheEnable();
    temp = read_sctlr();
    if (!(temp & SCTLR_C))
        goto EXIT;

    uwRet = SRE_OK;
EXIT:
    SRE_DCacheEnable();
    //enable interrupt
    (VOID)__SRE_IntRestore(uwSave);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return uwRet;
}

/*icache_enable_disable*/
static UINT32 UT_SRE_CACHE_002()
{
    UINT32 uwRet = OS_FAIL;
    UINTPTR uwSave = 0;
    UINT32 temp;
    //disable interrupt
    uwSave = __SRE_IntLock();

    SRE_ICacheDisable();
    temp = read_sctlr();
    if ((temp & SCTLR_I))
        goto EXIT;

    SRE_ICacheEnable();
    temp = read_sctlr();
    if (!(temp & SCTLR_I))
        goto EXIT;

    uwRet = SRE_OK;
EXIT:
    SRE_ICacheEnable();
    //enable interrupt
    (VOID)__SRE_IntRestore(uwSave);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return uwRet;
}


/*cache_flushall*/
static UINT32 UT_SRE_CACHE_003()
{
    UINT32 uwRet = OS_FAIL;
    UINTPTR uwSave = 0;

    uwSave = __SRE_IntLock();

    SRE_CacheFlushAll();

    uwRet = SRE_OK;

    //enable interrupt
    (VOID)__SRE_IntRestore(uwSave);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return uwRet;
}

/*tlb_flushall*/
static UINT32 UT_SRE_CACHE_004()
{
    UINT32 uwRet = OS_FAIL;
    UINTPTR uwSave = 0;
    //disable interrupt
    uwSave = __SRE_IntLock();

    flush_tlb_all();

    uwRet = SRE_OK;

    //enable interrupt
    (VOID)__SRE_IntRestore(uwSave);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return uwRet;
}

static inline void fill_mem(UINT32* addr, UINT32 size, UINT32 val){

    __volatile__ UINT32 temp = val;
    __asm__ __volatile__(

                         "mov r0, %0\n"

                         "add r1, r0, %1\n"

                         "1: str %2, [r0] ,#0x4\n"
                         "cmp r0, r1\n"
                         "bcc 1b\n"

                         :
                         :"r"(addr),"r"(size),"r"(temp)
                         :"r0","r1"
                         );
};

static inline void touch_mem(UINT32* addr, UINT32 size){

    __volatile__ UINT32 temp;
    __asm__ __volatile__(

                         "mov r0, %0\n"

                         "add r1, r0, %1\n"

                         "1: ldr %2, [r0] ,#0x4\n"
                         "cmp r0, r1\n"
                         "bcc 1b\n"

                         :
                         :"r"(addr),"r"(size),"r"(temp)
                         :"r0","r1"
                         );
};


#ifdef TEST_CACHE_DEBUG
static void show_mem(UINT32* paddr, UINT32 size) {
    UINT32 index;
    uart_printf("====================================\n");
    for (index=0; index<size/4; index++) {
        uart_printf("%d: val=0x%x, addr=0x%x\n", index, paddr[index], &paddr[index]);
    }
}
#else
#define show_mem(x, args...)
#endif


#if 0
#define TEST_NUM_X (32 * 2.5)
static UINT32 UT_dcache_enable_disable()
{
    UINT32 uwRet = OS_FAIL;
    UINTPTR uwSave = 0;

    //disable interrupt
    uwSave = __SRE_IntLock();

    SRE_CacheFlushAll();


    SRE_DCacheDisable();
    fill_mem(g_acTestBuf, TEST_NUM_X, CACHE_TEST_VALUE);//0x1234DDDD

    SRE_DCacheEnable();
    fill_mem(g_acTestBuf, TEST_NUM_X, CACHE_TEST_VALUE1);//0xA5A5A5A5
    SRE_DCacheDisable();
    //    SRE_DCacheInv(g_acTestBuf, TEST_NUM_X, TRUE);
    show_memx(g_acTestBuf, TEST_NUM_X);
    SRE_DCacheEnable();
    show_memx(g_acTestBuf, TEST_NUM_X);
    uwRet = SRE_OK;

    //enable interrupt
    (VOID)__SRE_IntRestore(uwSave);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
}
#endif

#define FUNC_SIZE 0x10
static UINT32 icache_test_func1(int a, int b)
{
    int ret;

    ret = a + b;

    return ret;
}


static UINT32 icache_test_func2(int a, int b)
{
    int ret;

    ret = a - b;

    return ret;
}


/*ICacheInvAll*/
static UINT32 UT_SRE_CacheInstruction_001()
{
    UINT32 uwReslt = 0;
    UINT32* addr;
    UINT32 (*pfunc)(int, int);
    UINT32 i;

    //func1
    addr = (UINT32*)icache_test_func1;

    memcpy(g_acTestBuf, addr, FUNC_SIZE);
    pfunc = (UINT32 (*)(int, int))g_acTestBuf;

    //clean to make visible to i-cache
    SRE_DCacheClean(g_acTestBuf, FUNC_SIZE, TRUE);
    osDsb();
    //ensuring the visibility of updates to instruction cache
    SRE_ICacheInvAll();
    osDsb();//cache operation
    osIsb();//i-cache done

    //ensure load to i-cache
    for (i=0; i< 50;i++) {
        uwReslt = pfunc(2,1);
    }

    ICUNIT_ASSERT_EQUAL(uwReslt, 3, uwReslt);
    //func2
    addr = (UINT32*)icache_test_func2;

    memcpy(g_acTestBuf, addr, FUNC_SIZE);
    //clean to make visible to i-cache
    SRE_DCacheClean(g_acTestBuf, FUNC_SIZE, TRUE);
    osDsb();
#if 0
    uwReslt = pfunc(2,1);

    ICUNIT_ASSERT_EQUAL(uwReslt, 3, uwReslt);
#endif
    //ensuring the visibility of updates to instruction cache
    SRE_ICacheInvAll();
    osDsb();//cache operation
    osIsb();//i-cache done

    uwReslt = pfunc(2,1);

    ICUNIT_ASSERT_EQUAL(uwReslt, 1, uwReslt);

    return SRE_OK;
}

/*SRE_ICacheInv*/
static UINT32 UT_SRE_CacheInstruction_002()
{
    UINT32 uwReslt = 0;
    UINT32 *addr;
    UINT32 (*pfunc)(int, int);
    UINT32 i;

    //func1
    addr = (UINT32*)icache_test_func1;
    memcpy(g_acTestBuf, addr, FUNC_SIZE);
    pfunc = (UINT32 (*)(int, int))g_acTestBuf;
    SRE_CacheFlushAll();
    for (i=0; i< 50;i++) {
        uwReslt = pfunc(2,1);
    }

    ICUNIT_ASSERT_EQUAL(uwReslt, 3, uwReslt);

    g_acTestBuf[0] = 0xe0610000;
    //clean to make visible to i-cache
    SRE_DCacheClean(g_acTestBuf, 4, TRUE);
    osDsb();
#if 0
    uwReslt = pfunc(2,1);
    ICUNIT_ASSERT_EQUAL(uwReslt, 3, uwReslt);
#endif

    //    SRE_ICacheInvAll();
    SRE_ICacheInv(g_acTestBuf, 4, TRUE);
    osDsb();
    osIsb();

    uwReslt = pfunc(2,1);
    ICUNIT_ASSERT_EQUAL(uwReslt, 1, uwReslt);

    return SRE_OK;
}


/*function: dcache disable, enable test*/
UINT32 UT_SRE_CacheData_001(VOID)
{
    UINT32 uwLoop = 0;
    UINT32 uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, 0x0);
    SRE_DCacheClean(g_acTestBuf, CACHE_TEST_SIZE, TRUE);
    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);
    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);
    SRE_DCacheDisable();

    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);

    uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);

    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }


    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);
    SRE_DCacheEnable();

    return SRE_OK;
}

/*dcache invalidate*/
UINT32 UT_SRE_CacheData_002(VOID)
{
    UINT32 uwLoop = 0;
    UINT32 uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, 0x0);

    SRE_DCacheCleanAll();

    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);

    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);

    SRE_DCacheInv(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    uwReslt = 0;
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }

    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);

    uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    return SRE_OK;

}

/*function: SRE_DCacheFlush*/
UINT32 UT_SRE_CacheData_003(VOID)
{
    UINT32 uwLoop = 0;
    UINT32 uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, 0x0);

    SRE_DCacheClean(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);

    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);

    SRE_DCacheFlush(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    uwReslt = 0;
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    return SRE_OK;

}

/*function: SRE_CacheFlushAll*/
UINT32 UT_SRE_CacheData_004(VOID)
{
    UINT32 uwLoop = 0;
    UINT32 uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, 0x0);
    SRE_DCacheClean(g_acTestBuf, CACHE_TEST_SIZE, TRUE);
    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);

    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);

    //clean cache before invalidate
    SRE_DCacheCleanAll();
    SRE_DCacheInv(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    uwReslt = 0;
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    uwReslt = 0;

    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);
    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    return SRE_OK;

}

/*A.1.disable dcache
  2.modify
  3.invalidate
  4.enable dcache
  B. invalidate
  C. Clean*/
UINT32 UT_SRE_CacheData_005(VOID)
{
    UINT32 uwLoop = 0;
    UINT32 uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, 0x0);
    SRE_DCacheCleanAll();

    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);

    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);

    SRE_DCacheDisable();

    uwReslt = 0;
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);


    SRE_DCacheEnable();
    SRE_DCacheInv(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, 0x0);
    SRE_DCacheClean(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);

    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE);

    SRE_DCacheInv(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);


    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);

    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);

    SRE_DCacheClean(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    return SRE_OK;

}


/*dcache invalidate*/
UINT32 UT_SRE_CacheData_007(VOID)
{
    UINT32 uwLoop = 0;
    UINT32 uwReslt = 0;

    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, 0x0);
    SRE_DCacheClean(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);

    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);

    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    //load to cache
    touch_mem(g_acTestBuf, CACHE_TEST_SIZE);

    //modify cache
    fill_mem(g_acTestBuf, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);


    SRE_DCacheInv(g_acTestBuf, CACHE_TEST_SIZE, TRUE);

    uwReslt = 0;

    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(g_acTestBuf[uwLoop] == CACHE_TEST_VALUE)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);


    return SRE_OK;

}

static void UT_SRE_MMU_test_backup(UINT32* addr){
    memcpy(g_memBackup, addr, CACHE_TEST_SIZE);
}

static void UT_SRE_MMU_test_restore(UINT32* addr){
    memcpy(addr, g_memBackup, CACHE_TEST_SIZE);
}

/*
flush_tlb_all
map_section_entry*/
static UINT32 UT_SRE_MMU_001()
{

    struct cpu_section desc;
    UINT32 buffer1, buffer2;
    UINT32 uwLoop;
    UINT32 uwReslt = 0;
    UINT32 *pbuf;

    desc.dom = SECURE_ACCESS_DOMAIN;
    desc.ap = PRIV_RW_USR_RW;
    desc.xn = L1_EXECUTE_ALLOW;
    desc.tex = 0x1;
    desc.c = 0x1;
    desc.b = 0x1;
    desc.ns = 0;
    desc.ng = 0;
    desc.s = 0;

    buffer1 = 0;
    buffer2 = (1<<20);

    desc.va = buffer1;
    desc.pa = 0;

    map_section_entry(secure_page_table, &desc, 0);

    desc.va = buffer2;
    desc.pa = 0;
    map_section_entry(secure_page_table, &desc, 0);

    flush_tlb_all();

    UT_SRE_MMU_test_backup((UINT32*)0);
    fill_mem((UINT32*)buffer2, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);
    fill_mem((UINT32*)buffer1, CACHE_TEST_SIZE, CACHE_TEST_VALUE);

    show_mem(secure_page_table, 2*4);


    show_mem((UINT32*)buffer2, 10*4);

    pbuf = (UINT32*)buffer1;
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(pbuf[uwLoop] == CACHE_TEST_VALUE)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    //restore
    UT_SRE_MMU_test_restore((UINT32*)0);
    fill_mem(secure_page_table, 2*4, 0);
    flush_tlb_all();

    return SRE_OK;
}


/*
flush_tlb_region
map_section_entry*/
static UINT32 UT_SRE_MMU_002()
{

    struct cpu_section desc;
    UINT32 buffer1, buffer2;
    UINT32 uwLoop;
    UINT32 uwReslt = 0;
    UINT32 *pbuf;

    desc.dom = SECURE_ACCESS_DOMAIN;
    desc.ap = PRIV_RW_USR_RW;
    desc.xn = L1_EXECUTE_ALLOW;
    desc.tex = 0x1;
    desc.c = 0x1;
    desc.b = 0x1;
    desc.ns = 0;
    desc.ng = 0;
    desc.s = 0;

    buffer1 = 0;
    buffer2 = (1<<20);

    desc.va = buffer1;
    desc.pa = 0;

    map_section_entry(secure_page_table, &desc, 0);

    desc.va = buffer2;
    desc.pa = 0;
    map_section_entry(secure_page_table, &desc, 0);


    flush_tlb_region((UINT32*)(buffer1&~0xfff));
    flush_tlb_region((UINT32*)(buffer2&~0xfff));

    UT_SRE_MMU_test_backup((UINT32*)0);
    fill_mem((UINT32*)buffer2, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);
    fill_mem((UINT32*)buffer1, CACHE_TEST_SIZE, CACHE_TEST_VALUE);

    show_mem((UINT32*)secure_page_table, 2*4);


    show_mem((UINT32*)buffer2, 10*4);

    pbuf = (UINT32*)buffer1;
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(pbuf[uwLoop] == CACHE_TEST_VALUE)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    //restore
    UT_SRE_MMU_test_restore((UINT32*)0);
    fill_mem((UINT32*)secure_page_table, 2*4, 0);
    flush_tlb_region((UINT32*)(buffer1&~0xfff));
    flush_tlb_region((UINT32*)(buffer2&~0xfff));


    return SRE_OK;
}

/*
disable mmu
map_section_entry*/
static UINT32 UT_SRE_MMU_003()
{

    struct cpu_section desc;
    UINT32 buffer1, buffer2;
    UINT32 uwLoop;
    UINT32 uwReslt = 0;
    UINT32 reg_val;
    UINT32 *pbuf;

    /*disable mmu*/
    SRE_CacheFlushAll();
    reg_val = read_sctlr();
    reg_val = reg_val & ~(SCTLR_M);
    write_sctlr(reg_val);

    desc.dom = SECURE_ACCESS_DOMAIN;
    desc.ap = PRIV_RW_USR_RW;
    desc.xn = L1_EXECUTE_ALLOW;
    desc.tex = 0x1;
    desc.c = 0x1;
    desc.b = 0x1;
    desc.ns = 0;
    desc.ng = 0;
    desc.s = 0;

    buffer1 = 0;
    buffer2 = 1<<20;

    UT_SRE_MMU_test_backup((UINT32*)buffer1);
    fill_mem((UINT32*)buffer1, CACHE_TEST_SIZE, CACHE_TEST_VALUE1);

    desc.va = buffer1;
    desc.pa = 0;

    map_section_entry(secure_page_table, &desc, 0);

    desc.va = buffer2;
    desc.pa = 0;
    map_section_entry(secure_page_table, &desc, 0);


    /*enable mmu*/
    flush_tlb_all();

    reg_val = read_sctlr();
    reg_val = reg_val | (SCTLR_M);
    write_sctlr(reg_val);


    show_mem(secure_page_table, 2*4);


    show_mem((UINT32*)buffer2, 10*4);

    pbuf = (UINT32*)buffer1;
    for(uwLoop = 0; uwLoop < CACHE_TEST_NUM; uwLoop++)
    {
        if(pbuf[uwLoop] == CACHE_TEST_VALUE1)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, CACHE_TEST_NUM, uwReslt);

    //restore
    UT_SRE_MMU_test_restore((UINT32*)buffer1);
    fill_mem(secure_page_table, 2*4, 0);
    flush_tlb_region((UINT32*)(buffer1&~0xfff));
    flush_tlb_region((UINT32*)(buffer2&~0xfff));

#if 0
    for (uwLoop =0; uwLoop< 100; uwLoop++)
        uart_printf("%d:::buffer2 content=%x\n", uwLoop, *(UINT32*)buffer2);
#endif
    return SRE_OK;
}


void UT_uni_cachemmu(void)
{
    iUINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_uni_cache");

    //TEST_ADD_CASE(UT_cache_info, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CACHE_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CACHE_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CACHE_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CACHE_004, uiSuiteId, Label_RUN);

    //TEST_ADD_CASE(UT_dcache_enable_disable, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_CacheData_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CacheData_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CacheData_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CacheData_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CacheData_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CacheData_007, uiSuiteId, Label_RUN);


    TEST_ADD_CASE(UT_SRE_MMU_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MMU_002, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_MMU_003, uiSuiteId, Label_RUN);


    TEST_ADD_CASE(UT_SRE_CacheInstruction_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CacheInstruction_002, uiSuiteId, Label_RUN);

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}
