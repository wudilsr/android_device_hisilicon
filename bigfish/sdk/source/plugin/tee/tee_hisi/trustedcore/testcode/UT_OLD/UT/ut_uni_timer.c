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
#include "sre_hwi.h"
#include "secure_gic_init.h"
#include "iCunit.h"
#include "sre_secure_timer.h"
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

timer_event* tzhypsched_event1, * tzhypsched_event2, * tzhypsched_event3;
timeval_t tzhypsched_time1, tzhypsched_time2, tzhypsched_time3;

extern volatile OS_IDLE_HOOK m_pfnSysIdleHook;

volatile UINT32 guwtimer_gone_test = 0;

extern UINT64 __SRE_ReadTimestamp(VOID);
OS_SEC_TEXT_UT void echo_task_handler1(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;

    uart_printf("excute the echo_task_handler11111111\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 12, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    guwtimer_gone_test = 1;
    //uart_printf("guwtimer_gone_test: %d\n", guwtimer_gone_test);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT void echo_task_handler2(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;

    uart_printf("excute the echo_task_handler22222222\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 18, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT UINT32 UT_TimerCreate_001()
{

    UINT32  uwTestData1 = 12;
    UINT32  uwTestData2 = 18;
    UINT32  uwTest = 0;

#if 1
    tzhypsched_event1 = __SRE_TimerEventCreate(&echo_task_handler1,(void*)uwTestData1);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event1, NULL, tzhypsched_event1);

    /* Time duration = 40ms */
    tzhypsched_time1.tval.nsec = 40000000;
    tzhypsched_time1.tval.sec = 0;

    __SRE_TimerEventStart(tzhypsched_event1, &tzhypsched_time1);

    tzhypsched_event2 = __SRE_TimerEventCreate(&echo_task_handler2,(void*)uwTestData2);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event2, NULL, tzhypsched_event2);

    /* Time duration = 20ms */
    tzhypsched_time2.tval.nsec = 20000000;
    tzhypsched_time2.tval.sec = 0;

    __SRE_TimerEventStart(tzhypsched_event2, &tzhypsched_time2);

    while(guwtimer_gone_test == 0)
    {
        uwTest++;
        //uart_printf("guwtimer_gone_test: %d\n", guwtimer_gone_test);
    }
    //uart_printf("guwtimer_gone_test: %d\n", guwtimer_gone_test);
    guwtimer_gone_test = 0;

#endif

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT void echo_task_handler5(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;

    uart_printf("excute the echo_task_handler55555555\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 35, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT void echo_task_handler3(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;
    UINT32  uwTestData3 = 35;

    uart_printf("excute the echo_task_handler33333333\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 32, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    tzhypsched_event1 = __SRE_TimerEventCreate(&echo_task_handler5,(void*)uwTestData3);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event1, NULL, tzhypsched_event1);

    /* Time duration = 61s */
    tzhypsched_time1.tval.nsec = 0;
    tzhypsched_time1.tval.sec = 1;  /*timer1时间为60s*/

    __SRE_TimerEventStart(tzhypsched_event1, &tzhypsched_time1);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT void echo_task_handler4(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;

    uart_printf("excute the echo_task_handler44444444\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 36, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT UINT32 UT_TimerCreate_002()
{

    UINT32  uwTestData1 = 32;
    UINT32  uwTestData2 = 36;

#if 1
    tzhypsched_event1 = __SRE_TimerEventCreate(&echo_task_handler3,(void*)uwTestData1);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event1, NULL, tzhypsched_event1);

    /* Time duration = 60s */
    tzhypsched_time1.tval.nsec = 0;
    tzhypsched_time1.tval.sec = 60;

    __SRE_TimerEventStart(tzhypsched_event1, &tzhypsched_time1);


    tzhypsched_event2 = __SRE_TimerEventCreate(&echo_task_handler4,(void*)uwTestData2);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event2, NULL, tzhypsched_event2);

    /* Time duration = 63s */
    tzhypsched_time2.tval.nsec = 0;
    tzhypsched_time2.tval.sec = 63;

    __SRE_TimerEventStart(tzhypsched_event2, &tzhypsched_time2);

#endif

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT void echo_task_handler8(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;

    uart_printf("excute the echo_task_handler88888888\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 68, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT void echo_task_handler6(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;
    UINT32  uwTestData3 = 68;

    uart_printf("excute the echo_task_handler66666666\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 66, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    tzhypsched_event1 = __SRE_TimerEventCreate(&echo_task_handler8,(void*)uwTestData3);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event1, NULL, tzhypsched_event1);

    /* Time duration = 61s */
    tzhypsched_time1.tval.nsec = 0;
    tzhypsched_time1.tval.sec = 1;  /*timer1时间为60s*/

    __SRE_TimerEventStart(tzhypsched_event1, &tzhypsched_time1);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT void echo_task_handler7(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;

    uart_printf("excute the echo_task_handler77777777\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 67, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT UINT32 UT_TimerCreate_003()
{

    UINT32  uwTestData1 = 66;
    UINT32  uwTestData2 = 67;

#if 1
    tzhypsched_event1 = __SRE_TimerEventCreate(&echo_task_handler6,(void*)uwTestData1);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event1, NULL, tzhypsched_event1);

    /* Time duration = 90s */
    tzhypsched_time1.tval.nsec = 0;
    tzhypsched_time1.tval.sec = 90;

    __SRE_TimerEventStart(tzhypsched_event1, &tzhypsched_time1);


    tzhypsched_event2 = __SRE_TimerEventCreate(&echo_task_handler7,(void*)uwTestData2);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event2, NULL, tzhypsched_event2);

    /* Time duration = 93s */
    tzhypsched_time2.tval.nsec = 0;
    tzhypsched_time2.tval.sec = 93;

    __SRE_TimerEventStart(tzhypsched_event2, &tzhypsched_time2);

#endif

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT void echo_task_handler10(timer_event* tevent)
{
    UINT32 uwRet;
    UINT32 uwPara;
    UINT32  uwTestData3 = 88;

    uart_printf("excute the echo_task_handler10a10a10a\n");

    uwPara = (UINT32)tevent->data;

    uart_printf("uwPara: %d\n", uwPara);

    ICUNIT_ASSERT_EQUAL(uwPara, 86, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
#if 0
    tzhypsched_event1 = __SRE_TimerEventCreate(&echo_task_handler8,(void*)uwTestData3);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event1, NULL, tzhypsched_event1);

    /* Time duration = 61s */
    tzhypsched_time1.tval.nsec = 0;
    tzhypsched_time1.tval.sec = 1;  /*timer1时间为60s*/

    __SRE_TimerEventStart(tzhypsched_event1, &tzhypsched_time1);
#endif
    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT void echo_task_handler11(timer_event* tevent)
{
    UINT32 uwRet;
    timer_event *puwPara;

    uart_printf("excute the echo_task_handler11a11a11\n");

    puwPara = (timer_event *)tevent->data;

    uart_printf("uwPara: 0x%x\n", puwPara);

    //ICUNIT_ASSERT_EQUAL(uwPara, 87, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    //SRE_TimerEventStop(puwPara);

    //uart_printf("excute the echo_task_handler\n");
}

OS_SEC_TEXT_UT void echo_task_handler12(timer_event* tevent)
{
    UINT32 uwRet;
    timer_event *puwPara;

    uart_printf("excute the echo_task_handler12a12a12\n");

    puwPara = (timer_event *)tevent->data;

    uart_printf("uwPara: 0x%x\n", puwPara);

    //ICUNIT_ASSERT_EQUAL(uwPara, 87, uwPara);

    tevent->state &= ~TIMER_STATE_EXECUTING;

    uwRet = __SRE_TimerEventDestroy(tevent);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    __SRE_TimerEventStop(puwPara);

    //uart_printf("excute the echo_task_handler\n");
}


OS_SEC_TEXT_UT UINT32 UT_TimerCreate_004()
{

    UINT32  uwTestData1 = 86;
    UINT32  uwTestData2 = 87;

#if 1
    tzhypsched_event1 = __SRE_TimerEventCreate(&echo_task_handler10,(void*)uwTestData1);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event1, NULL, tzhypsched_event1);

    /* Time duration = 123s */
    tzhypsched_time1.tval.nsec = 0;
    tzhypsched_time1.tval.sec = 123;

    __SRE_TimerEventStart(tzhypsched_event1, &tzhypsched_time1);

    //uart_printf("tzhypsched_event1 = 0x%x", tzhypsched_event1);
    tzhypsched_event2 = __SRE_TimerEventCreate(&echo_task_handler11,(void*)tzhypsched_event1);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event2, NULL, tzhypsched_event2);

    /* Time duration = 120s */
    tzhypsched_time2.tval.nsec = 0;
    tzhypsched_time2.tval.sec = 120;

    __SRE_TimerEventStart(tzhypsched_event2, &tzhypsched_time2);

#endif

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_TimerCreate_005()
{

    UINT32  uwTestData1 = 86;
#if 1
    tzhypsched_event1 = __SRE_TimerEventCreate(&echo_task_handler10,(void*)uwTestData1);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event1, NULL, tzhypsched_event1);

    /* Time duration = 133s */
    tzhypsched_time1.tval.nsec = 0;
    tzhypsched_time1.tval.sec = 133;

    __SRE_TimerEventStart(tzhypsched_event1, &tzhypsched_time1);

    //uart_printf("tzhypsched_event1 = 0x%x", tzhypsched_event1);
    tzhypsched_event2 = __SRE_TimerEventCreate(&echo_task_handler12,(void*)tzhypsched_event1);
    ICUNIT_ASSERT_NOT_EQUAL(tzhypsched_event2, NULL, tzhypsched_event2);

    /* Time duration = 130s */
    tzhypsched_time2.tval.nsec = 0;
    tzhypsched_time2.tval.sec = 130;

    __SRE_TimerEventStart(tzhypsched_event2, &tzhypsched_time2);

#endif

EXIT:
    return SRE_OK;
}

OS_SEC_TEXT_UT void UT_Timerdelay_001(void)
{
    __SRE_SwMsleep(1000);
}

OS_SEC_TEXT_UT void UT_Timerdelay_002(void)
{
    UINT32 uwRet;

    uwRet = __SRE_SwMsleep(1001);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TIMER_INTERVAL_INVALID, uwRet);

}

OS_SEC_TEXT_UT void UT_ReadSystemTimer_001(void)
{
    UINTPTR uvIntSave;
    INT64  illTimer1, illTimer2;
    INT32  ilSecNum1 = 0, ilSecNum2 = 0;

    uvIntSave = __SRE_IntLock();

    illTimer1 = __SRE_ReadTimestamp();
    ilSecNum1 = (INT32)(illTimer1 >> 32);
    uart_printf("illTimer2 sec = 0x%x\n", ilSecNum1);

    ilSecNum2 = ilSecNum1;

    while(ilSecNum2 -ilSecNum1 < 1) //waiting for 2s
    {
        illTimer2 = __SRE_ReadTimestamp();
        ilSecNum2 = (INT32)(illTimer2 >> 32);
        uart_printf("illTimer3 sec = 0x%x\n", ilSecNum2);
    }

    __SRE_IntRestore(uvIntSave);

    return SRE_OK;

}

OS_SEC_TEXT_UT void UT_TimerEventStart_001(void)
{
    timer_event *puwPara;
    timeval_t     illTimer;
    UINT32       uwRet = 0;

    illTimer.tval.nsec = NSECS_PER_SEC;
    illTimer.tval.sec = 0;

    uwRet = __SRE_TimerEventStart(puwPara, &illTimer);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TIMER_INTERVAL_INVALID, uwRet);

    illTimer.tval.nsec = 0;
    illTimer.tval.sec = 0x80000000;

    uwRet = __SRE_TimerEventStart(puwPara, &illTimer);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TIMER_INTERVAL_INVALID, uwRet);

    puwPara = NULL;

    illTimer.tval.nsec = 0;
    illTimer.tval.sec = 1;

    uwRet = __SRE_TimerEventStart(puwPara, &illTimer);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TIMER_INPUT_PTR_NULL, uwRet);

    return;
}

OS_SEC_TEXT_UT void UT_uni_timer(void)
{
    iUINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_Timer");

    TEST_ADD_CASE(UT_Timerdelay_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_Timerdelay_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_ReadSystemTimer_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_TimerEventStart_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_TimerCreate_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_TimerCreate_002, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_TimerCreate_003, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_TimerCreate_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_TimerCreate_005, uiSuiteId, Label_RUN);

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
