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
#include "sre_hwi.ph"
#include "sre_hwi.h"
#include "secure_gic_init.h"
#include "iCunit.h"
#include "sre_ticktimer.h"
#include "app_data_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_A9)
#if 0
	__asm UINT32 osGetPeriBaseAddr_T(VOID)
{
! "r0"
    mrc p15, 4, r0, c15, c0, 0
}
#endif

volatile UINT32 g_uwRetTest = 0;
volatile UINT32 g_uwRetTest1 = 1;
volatile UINT32 guw_HwiTestHandleValue1 = 0;
volatile UINT32 guw_HwiTestHandleValue2 = 0;
volatile UINT32 guw_HwiTestValue1 = 0;

extern UINT64 __SRE_ReadTimestamp(VOID);

OS_SEC_TEXT_UT UINT32 SRE_HwiTrigger_T(HWI_HANDLE_T  uwHwiNum)
{
    UINT32 uwCoreId;

    *((volatile UINT32 *)(GIC_ID_PHY_BASE + 0xF00)) = 0x10000 + uwHwiNum;
}

OS_SEC_TEXT_UT UINT32 UT_HwiQT_Func1()
{
    uart_printf("########step into UT_HwiQT_Func1!\n");
    g_uwRetTest++;
    ICUNIT_ASSERT_EQUAL(g_uwRetTest, 1, g_uwRetTest);
}

OS_SEC_TEXT_UT UINT32 UT_Hwi_Func1(HWI_ARG_T uwArg)
{
    UINT32 uwRet;

    uart_printf("########step into UT_Hwi_Func1!\n");

    uwRet = __SRE_HwiCreate(0, 0xa0, INT_SECURE, UT_HwiQT_Func1, 0);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_HwiEnable(0);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    __SRE_HwiTrigger(INT_SECURE, 0, 0);
}

OS_SEC_TEXT_UT UINT32 UT_HwiSgiCreate_001()
{
    UINT32 uwRet;
    UINT32 uwPerBaseAddr;


    uwRet = __SRE_HwiCreate(1, 0xa0, INT_SECURE, UT_Hwi_Func1, 1);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    uwRet = __SRE_HwiEnable(1);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    __SRE_HwiTrigger(INT_SECURE, 0, 1);

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    uwRet = __SRE_HwiDelete(0);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);


EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_HwiQT_Func2()
{
    uart_printf("########step into UT_HwiQT_Func2!\n");
    g_uwRetTest1++;
    ICUNIT_ASSERT_EQUAL(g_uwRetTest1, 2, g_uwRetTest1);
}

OS_SEC_TEXT_UT UINT32 UT_Hwi_Func2(HWI_ARG_T uwArg)
{
    UINT32 uwRet;

    uart_printf("########step into UT_Hwi_Func2!\n");

    uwRet = __SRE_HwiCreate(8, 0xa0, INT_UNSECURE, UT_HwiQT_Func2, 8);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_HwiEnable(8);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    __SRE_HwiTrigger(INT_UNSECURE, 0, 8);
}

OS_SEC_TEXT_UT UINT32 UT_HwiSgiCreate_002()
{
    UINT32 uwRet;
    UINT32 uwPerBaseAddr;
    UINT32  uvIntSave;

    uvIntSave = __SRE_IntLock();
    uart_printf("****************uvIntSave1 = 0x%x\n", uvIntSave);
    __SRE_IntRestore(uvIntSave);

    uvIntSave = __SRE_IntLock();
    uart_printf("****************uvIntSave2 = 0x%x\n", uvIntSave);
    __SRE_IntRestore(uvIntSave);

    uwRet = SRE_HwiCreate(15, 0xa0, INT_UNSECURE, UT_Hwi_Func2, 15);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    uwRet = SRE_HwiEnable(15);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    SRE_HwiTrigger(INT_UNSECURE, 0, 15);

    uwRet = SRE_HwiDelete(15);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    uwRet = SRE_HwiDelete(8);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);


EXIT:
    return SRE_OK;
}
#endif

/* DTS: l00202565 add for ut test begin */
OS_SEC_TEXT_UT UINT32 HWI_handle(UINT32 arg)
{
    uart_printf("HWI handle run, the arg is:%x\n", arg);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SRE_HwiCreate(void)
{
    UINT32 uwRet;

    //uwRet = SRE_HwiCreate(35, 0xa0, 1, UT_Hwi_Func2, 15);
    //ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    uwRet = __SRE_HwiCreate(15, 0xa0, 3, UT_Hwi_Func2, 15);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_HWI_MODE_ERROR,uwRet, EXIT);

    uwRet = __SRE_HwiCreate(257, 0xa0, 1, UT_Hwi_Func2, 15);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_HWI_NUM_INVALID,uwRet, EXIT);

    uwRet = __SRE_HwiCreate(15, 257, 1, UT_Hwi_Func2, 15);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_HWI_PRIORITY_VALUE,uwRet, EXIT);

    uwRet = __SRE_HwiCreate(15, 0xa0, 1, NULL, 15);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_HWI_PROC_FUNC_NULL,uwRet, EXIT);

    m_astHwiForm[15].pfnHook = UT_Hwi_Func2;
    uwRet = __SRE_HwiCreate(15, 0xa0, 1, UT_Hwi_Func2, 15);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_HWI_ALREADY_CREATED,uwRet, EXIT);

    m_astHwiForm[15].pfnHook = osHwiDefaultHandler;
    uwRet = __SRE_HwiCreate(15, 0xa0, 1, UT_Hwi_Func2, 15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK,uwRet, EXIT);

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SRE_HwiDelete(void)
{
    UINT32 uwRet;
    uwRet = __SRE_HwiDelete(OS_HWI_MAX_NUM);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(16);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_DELETED, uwRet, EXIT);

     uwRet = __SRE_HwiDelete(15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SRE_HwiEnable(void)
{
    UINT32 uwRet;
    uwRet = __SRE_HwiEnable(OS_HWI_MAX_NUM);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

    uwRet = __SRE_HwiEnable(16);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SRE_HwiDisable(void)
{
    UINT32 uwRet;
    uwRet = __SRE_HwiDisable(OS_HWI_MAX_NUM);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

    uwRet = __SRE_HwiDisable(16);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT VOID UT_SRE_HwiTrigger_Handle1(UINT32 uwPara)
{
    ICUNIT_ASSERT_EQUAL(uwPara, 111, uwPara);
    guw_HwiTestHandleValue1 = 1;
}

OS_SEC_TEXT_UT UINT32 UT_SRE_HwiTrigger(void)
{
    UINT32 uwRet;
    UINT32 uwLoopValue = 0;

#if 0
    uwRet = __SRE_HwiCreate(0, 0xa0, INT_UNSECURE, UT_SRE_HwiTrigger_Handle1, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_MODE_ERROR, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    while(guw_HwiTestHandleValue1 != 1)
    {
        uwLoopValue++;
    }

    guw_HwiTestHandleValue1 = 0;

    uwRet = __SRE_HwiDelete(0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
#endif
    uwRet = __SRE_HwiCreate(0, 0xa0, INT_SECURE, UT_SRE_HwiTrigger_Handle1, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_MODE_ERROR, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    while(guw_HwiTestHandleValue1 != 1)
    {
        uwLoopValue++;
    }

    guw_HwiTestHandleValue1 = 0;

#if 0  /*对android kernel启动有影响*/
    uwRet = SRE_HwiTrigger(INT_UNSECURE, 1, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = SRE_HwiTrigger(INT_UNSECURE, 2, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = SRE_HwiTrigger(INT_UNSECURE, 3, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
#endif

    uwRet = __SRE_HwiTrigger(INT_SECURE, 4, 0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_CORE_ID_INVALID, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 16);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT VOID UT_HWI_FUNCTION_001_Handle1(UINT32 uwPara)
{
    ICUNIT_ASSERT_EQUAL(uwPara, 111, uwPara);
    guw_HwiTestHandleValue1 = 1;
}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_001(void)
{
    UINT32 uwRet;
    UINT32 uwLoopValue = 0;

    /*create intrrupt id:15*/
    uwRet = __SRE_HwiCreate(15, 0x10, INT_SECURE, UT_HWI_FUNCTION_001_Handle1, 111);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_PRIORITY_VALUE, uwRet, EXIT);

    uwRet = __SRE_HwiCreate(15, 0xa0, INT_SECURE, UT_HWI_FUNCTION_001_Handle1, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiEnable(15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    while(guw_HwiTestHandleValue1 != 1)
    {
        uwLoopValue++;
    }

    guw_HwiTestHandleValue1 = 0;

    uwRet = __SRE_HwiDisable(15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    while(guw_HwiTestHandleValue1 != 1)
    {
        uwLoopValue++;
    }

    guw_HwiTestHandleValue1 = 0;

    uwRet = __SRE_HwiDelete(15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_002(void)
{
    UINT32 uwRet;

    /*create intrrupt id:45*/
    uwRet = __SRE_HwiCreate(45, 0xa0, INT_UNSECURE, HWI_handle, 222);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiEnable(45);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 45);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

    uwRet = __SRE_HwiDisable(45);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 45);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(45);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 45);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

EXIT:
    return SRE_OK;

}

OS_SEC_TEXT_UT VOID UT_HWI_FUNCTION_003_Handle1(UINT32 uwPara)
{
    ICUNIT_ASSERT_EQUAL(uwPara, 111, uwPara);
    guw_HwiTestHandleValue1 = 1;
}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_003(void)
{
    UINT32 uwRet;
    UINT32 uwLoopValue;

    /*create intrrupt id:1*/
    uwRet = __SRE_HwiCreate(1, 0xa0, INT_SECURE, UT_HWI_FUNCTION_003_Handle1, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    while(guw_HwiTestHandleValue1 != 1)
    {
        uwLoopValue++;
    }

    ICUNIT_ASSERT_EQUAL(guw_HwiTestHandleValue1, 1, guw_HwiTestHandleValue1);

    guw_HwiTestHandleValue1 = 0;

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    //uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 1);
    //ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD, uwRet, EXIT);

EXIT:
    return SRE_OK;

}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_004(void)
{
    UINT32 uwRet;

    /*create intrrupt id:15*/
    uwRet = __SRE_HwiCreate(15, 0xa0, INT_SECURE, HWI_handle, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiEnable(15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiDisable(15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(15);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 15);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD, uwRet, EXIT);

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_005(void)
{
    UINT32 uwRet;

    /*create intrrupt id:45*/
    uwRet = __SRE_HwiCreate(45, 0xa0, INT_SECURE, HWI_handle, 222);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiEnable(45);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 45);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

    uwRet = __SRE_HwiDisable(45);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 45);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(45);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 45);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_INVALID, uwRet, EXIT);

EXIT:
    return SRE_OK;

}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_006(void)
{
    UINT32 uwRet;

    /*create intrrupt id:15*/
    uwRet = __SRE_HwiCreate(1, 0xa0, INT_SECURE, HWI_handle, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD, uwRet, EXIT);

EXIT:
    return SRE_OK;

}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_007(void)
{
    UINT32 uwRet;

    /*create intrrupt id:1*/
    uwRet = __SRE_HwiCreate(1, 0xa0, INT_UNSECURE, HWI_handle, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD, uwRet, EXIT);

EXIT:
    return SRE_OK;

}
/* DTS: l00202565 add for ut test end */

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_008(void)
{
    UINT32 uwRet;

    /*create intrrupt id:1*/
    uwRet = __SRE_HwiCreate(1, 0xa0, INT_UNSECURE, HWI_handle, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_MODE_ERROR, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HWI_NUM_NOT_SOFT_TRIGGERD, uwRet, EXIT);

    uwRet = __SRE_HwiCreate(1, 0xa0, INT_SECURE, HWI_handle, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    return SRE_OK;

}

OS_SEC_TEXT_UT VOID UT_HwiHandle_test1(UINT32 uwPara)
{
    ICUNIT_ASSERT_EQUAL(uwPara, 111, uwPara);
    uart_printf("guw_HwiTestValue1******3= %d\n", guw_HwiTestValue1);
    guw_HwiTestValue1 = 1;
}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_009(void)
{
    UINT32 uwRet;
    UINT32 uwLoopValue = 0;

    /*create intrrupt id:1*/
    uwRet = __SRE_HwiCreate(1, 0xa0, INT_UNSECURE, UT_HwiHandle_test1, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_UNSECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    while(guw_HwiTestValue1 != 1)
    {
        uwLoopValue++;
    }

    ICUNIT_ASSERT_EQUAL(guw_HwiTestValue1, 1, guw_HwiTestValue1);

    guw_HwiTestValue1 = 0;
    uart_printf("guw_HwiTestValue1******0= %d\n", guw_HwiTestValue1);

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    return SRE_OK;

}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_010(void)
{
    UINT32 uwRet;
    UINT32 uwLoopValue = 0;
    UINTPTR uvIntSave;
    INT64  illTimer1, illTimer2, illTimer3;
    timeval_t tmp_timeval1, tmp_timeval2;
    INT32  ilSecNum1 = 0, ilSecNum2 = 0;
    UINT32 uwCpsSave = 0;

    __asm__ __volatile__("MRS   %0, cpsr\n"
        :"=r"(uwCpsSave) );

    uart_printf("uwCPSR = 0x%x\n", uwCpsSave);

    uvIntSave = __SRE_IntLock();

    __asm__ __volatile__("MRS   %0, cpsr\n"
        :"=r"(uwCpsSave) );

    uart_printf("uwCPSR = 0x%x\n", uwCpsSave);

    __SRE_IntRestore(uvIntSave);

    __asm__ __volatile__("MRS   %0, cpsr\n"
        :"=r"(uwCpsSave) );

    uart_printf("uwCPSR = 0x%x\n", uwCpsSave);


    uvIntSave = __SRE_IntLock();

    __asm__ __volatile__("MRS   %0, cpsr\n"
        :"=r"(uwCpsSave) );

    /*create intrrupt id:1*/
    uwRet = __SRE_HwiCreate(1, 0xa0, INT_SECURE, UT_HwiHandle_test1, 111);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiTrigger(INT_SECURE, 0, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    illTimer1 = __SRE_ReadTimestamp();
    tmp_timeval1 = (timeval_t)illTimer1;
    illTimer2 = illTimer1;
    tmp_timeval2 = (timeval_t)illTimer2;

    #if 0
    while(((UINT32)(ullTimer2 & 0xffffffff) - (UINT32)(ullTimer1 & 0xffffffff)) < 50000000) //waiting for 50ms
    {
        //uart_printf("interval sec = %d; nsec = %d\n", (UINT32)((ullTimer1 >> 32) & 0xffffffff), (UINT32)(ullTimer1 & 0xffffffff));
        //uart_printf("interval sec = %d; nsec = %d\n", (UINT32)((ullTimer2 >> 32) & 0xffffffff), (UINT32)(ullTimer2 & 0xffffffff));
        ullTimer2 = __SRE_ReadTimestamp();
        //uart_printf("interval sec = %d; nsec = %d\n", (UINT32)((ullTimer2 >> 32) & 0xffffffff), (UINT32)(ullTimer2 & 0xffffffff));
    }
    #endif

    #if 1
    uart_printf("sec = 0x%x, nsec = 0x%x\n", tmp_timeval1.tval.sec, tmp_timeval1.tval.nsec);
    while(illTimer2 -illTimer1 < (INT64)8589934592) //waiting for 2s
    {
        illTimer2 = __SRE_ReadTimestamp();
        tmp_timeval2 = (timeval_t)illTimer2;
        //uart_printf("sec = 0x%x, nsec = 0x%x\n", tmp_timeval2.tval.sec, tmp_timeval2.tval.nsec);
    }
    #endif

    ilSecNum1 = (INT32)(illTimer2 >> 32);
    uart_printf("illTimer2 sec = 0x%x\n", ilSecNum1);

    ilSecNum2 = ilSecNum1;

    while(ilSecNum2 -ilSecNum1 < 2) //waiting for 2s
    {
        illTimer3 = __SRE_ReadTimestamp();
        ilSecNum2 = (INT32)(illTimer3 >> 32);
        //uart_printf("illTimer3 sec = 0x%x\n", ilSecNum2);
    }

    uart_printf("guw_HwiTestValue1******2= %d\n", guw_HwiTestValue1);

    ICUNIT_ASSERT_EQUAL(guw_HwiTestValue1, 0, guw_HwiTestValue1);

    __SRE_IntRestore(uvIntSave);

    uart_printf("__SRE_GetCurrCPSR = 0x%x\n", __SRE_GetCurrCPSR());

    while(guw_HwiTestValue1 != 1)
    {
        uwLoopValue++;
    }

    ICUNIT_ASSERT_EQUAL(guw_HwiTestValue1, 1, guw_HwiTestValue1);

    guw_HwiTestValue1 = 0;

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    return SRE_OK;

}

OS_SEC_TEXT_UT VOID Itest_SreHwi_FuncA()
{
    UINTPTR uwIntSave = 0;

    uwIntSave = __SRE_IntLock();
    Itest_SreHwi_FuncB();
    __SRE_IntRestore(uwIntSave);
     return;
}

OS_SEC_TEXT_UT VOID Itest_SreHwi_FuncB()
{
    UINTPTR uwIntSave4 = 0;

    uwIntSave4 = __SRE_IntLock();
    __SRE_IntRestore(uwIntSave4);
    return;
}

OS_SEC_TEXT_UT UINTPTR getcpsr(void)
{
UINTPTR uwIntSave1 = 0;

    __asm__ __volatile__(
    "mrs %0, CPSR"
    :"=r"(uwIntSave1):"0"(uwIntSave1));
	return uwIntSave1;
}

OS_SEC_TEXT_UT UINT32 UT_HWI_FUNCTION_011()
{
    UINT32 uwRet;
    UINTPTR uwIntSave1 = 0;
    UINTPTR uwIntSave2 = 0;
    UINTPTR uwIntSave3 = 0;

/*test lock begin*/
    uart_printf("uwIntSave1, %x\n", uwIntSave1);
    uwIntSave1 = getcpsr();
    uart_printf("uwIntSave1, %x\n", uwIntSave1);

    __asm__ __volatile__("cpsid f");//关fiq

    uwIntSave2 = getcpsr();
    uart_printf("uwIntSave2, %x\n", uwIntSave2);

    Itest_SreHwi_FuncA();

    uwIntSave3 = getcpsr();
    uart_printf("uwIntSave3, %x\n", uwIntSave3);

    if (uwIntSave2 == uwIntSave3)
    {
        uart_printf("uwIntSave2 = uwIntSave3 \n");
    }

    ICUNIT_ASSERT_EQUAL(uwIntSave3, uwIntSave2, uwIntSave3);

    __SRE_IntRestore(uwIntSave1);

    return;
}




OS_SEC_TEXT_UT void UT_uni_hwi(void)
{
    iUINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_uni_hwi");

    TEST_ADD_CASE(UT_HWI_FUNCTION_003, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_HwiSgiCreate_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_HwiSgiCreate_002, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_HwiCreate, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_HwiDelete, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_HwiEnable, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_HwiDisable, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_HwiTrigger, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_HWI_FUNCTION_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_HWI_FUNCTION_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_HWI_FUNCTION_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_HWI_FUNCTION_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_HWI_FUNCTION_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_HWI_FUNCTION_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_HWI_FUNCTION_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_HWI_FUNCTION_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_HWI_FUNCTION_009, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_HWI_FUNCTION_010, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_HWI_FUNCTION_011, uiSuiteId, Label_RUN);

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
