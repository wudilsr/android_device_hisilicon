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

#include "sre_swi.h"
#include "sre_swi.ph"
#include "Set_Peg.h"
#include "sre_mem.h"
#include "iCunit.h"
#include "app_data_common.h"
//#include <string.h>
#include "sre_hw.ph"
#include "osTest.h"
#include "sre_hwi.h"
#include "sre_task.h"

extern UINT32 osSwiInit(VOID);
extern UINT32 osSwiRegister(SWI_MOD_INFO_S *pstModInfo);

extern UINT16 g_usSwiMaxNum;
//extern OS_MCSWI_ACTIVE_FUNC    g_pfnMcSwiActive;
extern SWI_PRIOR_T             g_usSwiPriorityLevel;

volatile UINT32  g_uwSwiTrigTime;
volatile UINT32  g_uwHwiTrigTime;
volatile UINT32  g_uwTskRunTime;
volatile UINT32  g_auwSwiPid[10];
volatile UINT32  g_uwSwiPid;
volatile UINT32  g_uwSwiPid2;
volatile UINT32  g_uwHwiNum;
volatile UINT32  g_uwCount;
volatile UINT32  m_uwSwiTest = 0;

/*软中断触发次数加1*/
OS_SEC_TEXT_UT VOID Hook_Swi_TrigTime_Inc(UINT32 uwArg)
{
    g_uwSwiTrigTime++;
}

/*硬中断触发次数加1*/
OS_SEC_TEXT_UT VOID Hook_Hwi_TrigTime_Inc(UINT32 uwArg)
{
    g_uwHwiTrigTime++;
}

OS_SEC_TEXT_UT VOID Hook_Swi_Trig_Hwi(UINT32 uwArg)
{
    UINT32 uwRet;
    volatile UINT32 uwCnt = 1000;

    __SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), g_uwHwiNum);
    while (g_uwHwiTrigTime != 1) uwCnt--; //延时
    ICUNIT_TRACK_EQUAL(g_uwHwiTrigTime, 1, g_uwHwiTrigTime); //硬中断抢占软中断
    g_uwSwiTrigTime++;
}

OS_SEC_TEXT_UT VOID Hook_SwI_Get_Self_PID(UINT32 uwArg)
{
    __SRE_SwiSelf(&g_auwSwiPid[g_uwSwiTrigTime++]);
}

/*激活低优先级或同优先级软中断*/
OS_SEC_TEXT_UT VOID Hook_Swi_ActNotHigherSwi(UINT32 uwArg)
{
    __SRE_SwiActivate(g_uwSwiPid); //激活低优先级或同优先级软中断

    ICUNIT_TRACK_EQUAL(g_uwSwiTrigTime, 0, g_uwSwiTrigTime);
    g_uwSwiTrigTime++;
}

/*激活高优先级软中断*/
OS_SEC_TEXT_UT VOID Hook_Swi_ActHigherSwi(UINT32 uwArg)
{
    __SRE_SwiActivate(g_uwSwiPid); //激活高优先级软中断

    ICUNIT_TRACK_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime);
    g_uwSwiTrigTime++;
}
#if 0
/**
*-@test  UT_SwiActivate_001
*-@tspec 激活软中断
*-@ttitle软中断ID非法(核号超出范围)
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    uwSwiID = COMPOSE_PID(OS_SYS_CORE_MAX_NUM + 1, g_usSwiMaxNum-1);
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MCHWI_DST_INVALID, uwRet);
    return SRE_OK;
}


/**
*-@test  UT_SwiActivate_002
*-@tspec 激活软中断
*-@ttitle核间软中断激活钩子为空
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_002()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    OS_MCSWI_ACTIVE_FUNC pfnMcSwiActive;
    UINTPTR uvIntSave;

    uwSwiID = COMPOSE_PID(SRE_GetMasterCore() + SRE_GetNumberOfCores(), g_usSwiMaxNum-1);

    if (SRE_GetNumberOfCores() > 1)
    {
        uvIntSave = __SRE_IntLock();

        pfnMcSwiActive = g_pfnMcSwiActive; //backup
        g_pfnMcSwiActive = osMcSwiActNullHandler;
        uwRet = __SRE_SwiActivate(uwSwiID);
        g_pfnMcSwiActive = pfnMcSwiActive; //restore

        __SRE_IntRestore(uvIntSave);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_MC_INT_FAIL, uwRet);
    }
    return SRE_OK;
}
#endif
/**
*-@test  UT_SwiActivate_003
*-@tspec 激活软中断
*-@ttitle软中断ID非法
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_003()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;

    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum);
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ACT_ID_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_004
*-@tspec 激活软中断
*-@ttitle软中断未创建。
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_004()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_ATTRIBUTE_S *pstSwiAttr;
    UINT16 usStatus;

    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum - 1);
    pstSwiAttr = &g_stSwiData.pstList[g_usSwiMaxNum - 1];

    usStatus = pstSwiAttr->usStatus;
    pstSwiAttr->usStatus = OS_SWI_UNUSED;
    uwRet = __SRE_SwiActivate(uwSwiID);

    pstSwiAttr->usStatus = usStatus;
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ACT_NOT_CREATED, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_005
*-@tspec 激活软中断
*-@ttitle任务中激活软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_005()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    SWI_PRIOR_T usPrior;
    SWI_INIT_PARA_S stInitPara;

    usPrior = 12;
    stInitPara.pcSwiName  = "ut_swi_005";
    stInitPara.usPriority = usPrior;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0x1234;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime,EXIT);
EXIT:
    if (0xff != uwSwiID)
    {
        (VOID)__SRE_SwiDelete(uwSwiID);
    }
    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_006
*-@tspec 激活软中断
*-@ttitle高优先级软中断里激活低优先级软中断，低优先级软中断不能抢占高优先级软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_006()
{
    UINT32 uwRet;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_006_low";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0x1234;

    g_uwSwiPid  =0xff;
    g_uwSwiPid2 =0xff;

    uwRet = __SRE_SwiCreate(&g_uwSwiPid, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_swi_006_high";
    stInitPara.usPriority = 3;
    stInitPara.pfnHandler = Hook_Swi_ActNotHigherSwi;
    stInitPara.uwInitValue = 0x1234;

    uwRet = __SRE_SwiCreate(&g_uwSwiPid2, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(g_uwSwiPid2); //先激活高优先级软中断
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 2, g_uwSwiTrigTime,EXIT); //两个软中断都应被响应

EXIT:
    if (0xff != g_uwSwiPid) (void)__SRE_SwiDelete(g_uwSwiPid);
    if (0xff != g_uwSwiPid2) (void)__SRE_SwiDelete(g_uwSwiPid2);

    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_007
*-@tspec 激活软中断
*-@ttitle软中断里激活同优先级软中断，同优先级软中断间不能互相抢占
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_007()
{
    UINT32 uwRet;
    SWI_INIT_PARA_S stInitPara;

    g_uwSwiPid  =0xff;
    g_uwSwiPid2 =0xff;

    stInitPara.pcSwiName  = "ut_swi_007_01";
    stInitPara.usPriority = 3;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0x1234;

    uwRet = __SRE_SwiCreate(&g_uwSwiPid, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_swi_007_02";
    stInitPara.pfnHandler = Hook_Swi_ActNotHigherSwi;

    uwRet = __SRE_SwiCreate(&g_uwSwiPid2, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(g_uwSwiPid2); //先激活其中一个软中断
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 2, g_uwSwiTrigTime,EXIT); //两个软中断都应被响应
EXIT:
    if (0xff != g_uwSwiPid) (void)__SRE_SwiDelete(g_uwSwiPid);
    if (0xff != g_uwSwiPid2) (void)__SRE_SwiDelete(g_uwSwiPid2);
    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_008
*-@tspec 激活软中断
*-@ttitle低优先级软中断里激活高优先级软中断,高优先级软中断抢占低优先级中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_008()
{
    UINT32 uwRet;
    SWI_INIT_PARA_S stInitPara;

    g_uwSwiPid  =0xff;
    g_uwSwiPid2 =0xff;

    stInitPara.pcSwiName  = "ut_swi_008_high";
    stInitPara.usPriority = 3;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0x1234;

    uwRet = __SRE_SwiCreate(&g_uwSwiPid, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_swi_008_low";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = Hook_Swi_ActHigherSwi;

    uwRet = __SRE_SwiCreate(&g_uwSwiPid2, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(g_uwSwiPid2); //先激活低优先级软中断
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 2, g_uwSwiTrigTime,EXIT);  //两个软中断都应被响应
EXIT:
    if (0xff != g_uwSwiPid) (void)__SRE_SwiDelete(g_uwSwiPid);
    if (0xff != g_uwSwiPid2) (void)__SRE_SwiDelete(g_uwSwiPid2);
    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_009
*-@tspec 激活软中断
*-@ttitle硬中断里激活软中断,软中断不能抢占硬中断
*/
OS_SEC_TEXT_UT VOID UT_HwiHook_SwiActivate_009(UINT32 uwArg)
{
    __SRE_SwiActivate(uwArg); //激活软中断
    ICUNIT_TRACK_EQUAL(g_uwSwiTrigTime, 0, g_uwSwiTrigTime); //软中断不被响应
    g_uwHwiTrigTime++;
    //uart_printf("UT_HwiHook_SwiActivate_009 ++\n");
}

OS_SEC_TEXT_UT UINT32 UT_SwiActivate_009()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    SWI_PRIOR_T usPrior = 3;
    UINT32 uwHwiNo = UT_HWI_EVENT_1;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_009";
    stInitPara.usPriority = usPrior;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0x1234;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

   // SRE_HwiSetAttr(uwHwiNo, 3, OS_HWI_MODE_ENGROSS);

    /*创建核间虚拟中断*/
    uwRet = __SRE_HwiCreate(uwHwiNo, 0xa0,IT_HWI_SECURE_MODE,UT_HwiHook_SwiActivate_009, uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    __SRE_HwiEnable(uwHwiNo);
    //ICUNIT_GOTO_EQUAL(uwRet, OS_SUCCESS, uwRet, EXIT);

    /*触发核间虚拟中断*/
    g_uwSwiTrigTime = 0;
    g_uwHwiTrigTime = 0;
	__SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), uwHwiNo);

    while (g_uwHwiTrigTime == 0)
    {
        ;
    }

    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT); //两个中断都应被响应
    ICUNIT_GOTO_EQUAL(g_uwHwiTrigTime, 1, g_uwHwiTrigTime, EXIT);
EXIT:
    (void)__SRE_SwiDelete(uwSwiID);
    (void)__SRE_HwiDelete(uwHwiNo);

    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_010
*-@tspec  激活软中断
*-@ttitle 1)创建5个软中断A,B,C,D,E, 优先级为A>B=C=D>E;
          2)Disable软中断
          3)激活5个软中断
          4)Enable软中断, 软中断HOOK被执行的顺序应该是A,B,C,D,E
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_010()
{
    UINT32 uwRet;
    SWI_HANDLE_T auwSwiID[5] = {0xff, 0xff, 0xff, 0xff};
    SWI_PRIOR_T usPriorLow = 7;
    UINT16 usPrioLvl = 0xff;
    SWI_INIT_PARA_S stInitPara;
    UINT32 i;

    stInitPara.pcSwiName  = "ut_swi_010_high";
    stInitPara.usPriority = usPriorLow - 2;
    stInitPara.pfnHandler = Hook_SwI_Get_Self_PID;
    stInitPara.uwInitValue = 0;

    /*创建4个软中断A,B,C,D*/
    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);  //A
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_swi_010_mid_01";
    stInitPara.usPriority = usPriorLow - 1;

    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);//B
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_010_02";
    uwRet = __SRE_SwiCreate(&auwSwiID[2], &stInitPara);//C
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_010_03";
    uwRet = __SRE_SwiCreate(&auwSwiID[3], &stInitPara);//D
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_010_low";
    stInitPara.usPriority = usPriorLow;
    uwRet = __SRE_SwiCreate(&auwSwiID[4], &stInitPara);  //E
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    /*关闭软中断*/
    usPrioLvl = __SRE_SwiDisable();

    /*激活软中断*/
    for (i = 0; i < 5; i++)
    {
        uwRet = __SRE_SwiActivate(auwSwiID[i]);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    }

    /*打开软中断*/
    for (i = 0; i < 5; i++)
    {
        g_auwSwiPid[i] = 0xff;
    }
    g_uwSwiTrigTime = 0;
    __SRE_SwiEnable(usPriorLow+1);

    /*CHECK*/
    for (i = 0; i < 5; i++)
    {
        ICUNIT_GOTO_EQUAL(g_auwSwiPid[i], auwSwiID[i], g_auwSwiPid[i], EXIT);
    }

EXIT:
    for (i = 0; i < 5; i++)
    {
        if (0xff != auwSwiID[i]) (void)__SRE_SwiDelete(auwSwiID[i]);
    }
    if (0xff != usPrioLvl) __SRE_SwiEnable(usPrioLvl); //恢复软中断原触发级别

    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_011
*-@tspec 激活软中断
*-@ttitle软中断里唤醒任务，任务不能抢占软中断
*/
VOID UT_TskHook_SwiActivate_011( UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4 )
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    g_uwTskRunTime++;

    uart_printf("UT_TskHook_SwiActivate_011 start\n");

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT VOID UT_SwiHook_SwiActivate_011(UINT32 uwArg)
{
    __SRE_TaskUnlock();
    __SRE_TaskResume(uwArg); //唤醒任务
    ICUNIT_TRACK_EQUAL(g_uwTskRunTime, 0, g_uwTskRunTime);
    g_uwSwiTrigTime++;

    uart_printf("UT_SwiHook_SwiActivate_011 end\n");
}

OS_SEC_TEXT_UT UINT32 UT_SwiActivate_011()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    SWI_PRIOR_T  usPrior;
    TSK_HANDLE_T uwTaskID = 0xff;
    TSK_INIT_PARAM_S stTskParam = {UT_TskHook_SwiActivate_011, 4, 0, 0,0,0,0, 0x400, "Tsk_inSwi", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    SWI_INIT_PARA_S stInitPara;

    uart_printf("UT_SwiActivate_011 start\n");

    __SRE_TaskLock();
    uwRet = __SRE_TaskCreate(&uwTaskID, &stTskParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usPrior = 12;
    stInitPara.pcSwiName  = "ut_swi_011";
    stInitPara.usPriority = usPrior;
    stInitPara.pfnHandler = UT_SwiHook_SwiActivate_011;
    stInitPara.uwInitValue = uwTaskID;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;
    g_uwTskRunTime = 0;

    uart_printf("UT_SwiActivate_011 excute here\n");

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime,EXIT);
    ICUNIT_GOTO_EQUAL(g_uwTskRunTime, 1, g_uwTskRunTime,EXIT);
EXIT:
    __SRE_TaskUnlock();
    if (0xff != uwSwiID) (void)__SRE_SwiDelete(uwSwiID);
    if (0xff != uwTaskID) (void)__SRE_TaskDelete(uwTaskID);
    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_012
*-@tspec 激活软中断
*-@ttitle软中断里触发硬中断，硬中断可以抢占软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_012()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    SWI_PRIOR_T usPrior = 3;
    SWI_INIT_PARA_S stInitPara;

    g_uwHwiNum = UT_HWI_EVENT_1;

    stInitPara.pcSwiName  = "ut_swi_012_high";
    stInitPara.usPriority = usPrior;
    stInitPara.pfnHandler = Hook_Swi_Trig_Hwi;
    stInitPara.uwInitValue = g_uwHwiNum;

    //SRE_HwiSetAttr(g_uwHwiNum, 3, OS_HWI_MODE_ENGROSS);

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    /*创建核间虚拟中断*/
    uwRet = __SRE_HwiCreate(g_uwHwiNum, 0xa0,IT_HWI_SECURE_MODE,Hook_Hwi_TrigTime_Inc, uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    __SRE_HwiEnable(g_uwHwiNum);
    //ICUNIT_GOTO_EQUAL(uwRet, OS_SUCCESS, uwRet, EXIT);

    /*激活软中断*/
    g_uwSwiTrigTime = 0;
    g_uwHwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwHwiTrigTime, 1, g_uwHwiTrigTime, EXIT);
EXIT:
    if (uwSwiID!=0xff) (void)__SRE_SwiDelete(uwSwiID);
     (void)__SRE_HwiDelete(g_uwHwiNum);

    return SRE_OK;
}

/**
*-@test  UT_SwiActivate_013
*-@tspec 激活软中断
*-@ttitle软中断A里触发高优先级软中断B，软中断B里激活软中断C，软中断A和C的优先级相等
         期望：高优先级软中断返回后，继续执行软中断A
*/
OS_SEC_TEXT_UT VOID UT_SwiHookA_SwiActivate_013(UINT32 uwArg)
{
    UINT32 uwRet;

    uwRet = __SRE_SwiActivate(uwArg);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_TRACK_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime); //高优先级软中断被响应，但同优先级软中断不被响应
    g_uwSwiTrigTime++;
}

OS_SEC_TEXT_UT VOID UT_SwiHookB_SwiActivate_013(UINT32 uwArg)
{
    UINT32 uwRet;

    uwRet = __SRE_SwiActivate(uwArg);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
    g_uwSwiTrigTime++;
}

OS_SEC_TEXT_UT UINT32 UT_SwiActivate_013()
{
    UINT32 i;
    UINT32 uwRet;
    SWI_HANDLE_T auwSwiID[3] = {0xff, 0xff, 0xff};
    SWI_PRIOR_T usPrior = 3;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_013_C";
    stInitPara.usPriority = usPrior;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = usPrior;

    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_013_B";
    stInitPara.usPriority = usPrior - 1;
    stInitPara.pfnHandler = UT_SwiHookB_SwiActivate_013;
    stInitPara.uwInitValue = auwSwiID[0];

    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_013_A";
    stInitPara.usPriority = usPrior;
    stInitPara.pfnHandler = UT_SwiHookA_SwiActivate_013;
    stInitPara.uwInitValue = auwSwiID[1];

    uwRet = __SRE_SwiCreate(&auwSwiID[2], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    /*激活软中断*/
    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(auwSwiID[2]);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 3, g_uwSwiTrigTime, EXIT);
EXIT:
    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        if (auwSwiID[i] != 0xff)  (void)__SRE_SwiDelete(auwSwiID[i]);
    }
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_014
*-@tspec  激活软中断
*-@ttitle 激活最低优先级的软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_014()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    SWI_INIT_PARA_S stInitPara;

    if (SWI_INVALID_IDX == g_uwIdleSwiID)
    {
        /*没有IDLE软中断，创建最低优先级的软中断*/
        stInitPara.pcSwiName  = "ut_swi_014_low";
        stInitPara.usPriority = OS_SWI_PRIORITY_LOWEST;
        stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
        stInitPara.uwInitValue = 0;
        uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);  //A
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

        /*激活软中断*/
        g_uwSwiTrigTime = 0;
        uwRet = __SRE_SwiActivate(uwSwiID);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
        ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);
    }
    else
    {
        /*IDLE软中断已经创建，创建次最低优先级的软中断*/
        stInitPara.pcSwiName  = "ut_swi_014_low";
        stInitPara.usPriority = OS_SWI_PRIORITY_LOWEST - 1;
        stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
        stInitPara.uwInitValue = 0;
        uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);  //A
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

        /*激活软中断*/
        g_uwSwiTrigTime = 0;
        uwRet = __SRE_SwiActivate(uwSwiID);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
        ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);
    }

    EXIT:
        if (0xff != uwSwiID) (void)__SRE_SwiDelete(uwSwiID);

    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_015
*-@tspec  激活软中断
*-@ttitle 激活最高优先级的软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_015()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_015_high";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    /*创建最高优先级的软中断*/
    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);  //A
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    /*激活软中断*/
    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);

EXIT:
    if (0xff != uwSwiID) (void)__SRE_SwiDelete(uwSwiID);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_016
*-@tspec  激活软中断
*-@ttitle 关中断的情况下激活软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_016()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_016_A";
    stInitPara.usPriority = 5;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);  //A
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    (VOID)__SRE_IntLock();  //关中断

    /*激活软中断*/
    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);

EXIT:
    (VOID)__SRE_IntUnLock();  //开中断
    if (0xff != uwSwiID) (void)__SRE_SwiDelete(uwSwiID);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_017
*-@tspec  激活软中断
*-@ttitle 关中断的情况下激活软中断，软中断里触发硬中断，硬中断能被响应
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_017()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    UINT32 uwHwiNo = 7;
    SWI_INIT_PARA_S stInitPara;

    g_uwHwiNum = UT_HWI_EVENT_1;

    //SRE_HwiSetAttr(g_uwHwiNum, 3, OS_HWI_MODE_ENGROSS);

    stInitPara.pcSwiName  = "ut_swi_017_A";
    stInitPara.usPriority = 5;
    stInitPara.pfnHandler = Hook_Swi_Trig_Hwi;
    stInitPara.uwInitValue = g_uwHwiNum;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);  //A
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiCreate(g_uwHwiNum,0xa0,IT_HWI_SECURE_MODE,Hook_Hwi_TrigTime_Inc, uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiEnable(g_uwHwiNum);
    //ICUNIT_GOTO_EQUAL(uwRet, OS_SUCCESS, uwRet, EXIT);

    (VOID)__SRE_IntLock();  //关中断

    /*激活软中断*/
    g_uwSwiTrigTime = 0;
    g_uwHwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwHwiTrigTime, 1, g_uwHwiTrigTime, EXIT);
EXIT:
    (VOID)__SRE_IntUnLock();  //开中断
    if (0xff != uwSwiID) (void)__SRE_SwiDelete(uwSwiID);
    (void)__SRE_HwiDelete(g_uwHwiNum);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_018
*-@tspec  激活软中断
*-@ttitle 1)激活低优先级软中断
          2)低优先级软中断里，关中断的情况下激活高优先级软中断
          3)高优先级软中断里触发硬中断，硬中断能被响应
          4)返回低优先级软中断后，再次触发硬中断，硬中断不能被响应
*/
/*激活高优先级软中断*/
OS_SEC_TEXT_UT VOID Hook_Swi_SwiActivate_018(UINT32 uwArg)
{
    volatile UINT32 uwCnt = 1000;
    (void)__SRE_IntLock(); //关中断
    __SRE_SwiActivate(uwArg); //激活高优先级软中断

    ICUNIT_TRACK_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime);
    ICUNIT_TRACK_EQUAL(g_uwHwiTrigTime, 1, g_uwHwiTrigTime); //切到另外一个线程，硬中断能被响应

    g_uwSwiTrigTime++;
    __SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), g_uwHwiNum);
    while(g_uwHwiTrigTime != 1)
    {
        uwCnt--;
    }
    ICUNIT_TRACK_EQUAL(g_uwHwiTrigTime, 1, g_uwHwiTrigTime); //关中断的情况下硬中断不被响应
    (void)__SRE_IntUnLock();
}

OS_SEC_TEXT_UT UINT32 UT_SwiActivate_018()
{
    UINT32 uwRet;
    SWI_HANDLE_T auwSwiID[2] = {0xff,0xff};
    SWI_INIT_PARA_S stInitPara;

    g_uwHwiNum = UT_HWI_EVENT_1;

    //SRE_HwiSetAttr(g_uwHwiNum, 3, OS_HWI_MODE_ENGROSS);

    stInitPara.pcSwiName  = "ut_swi_018_high";
    stInitPara.usPriority = 5;
    stInitPara.pfnHandler = Hook_Swi_Trig_Hwi;
    stInitPara.uwInitValue = g_uwHwiNum;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);  //high
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_018_low";
    stInitPara.usPriority = 8;
    stInitPara.pfnHandler = Hook_Swi_SwiActivate_018;
    stInitPara.uwInitValue = auwSwiID[0];

    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);  //Alow
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HwiCreate(g_uwHwiNum,0xa0,IT_HWI_SECURE_MODE, Hook_Hwi_TrigTime_Inc, auwSwiID[1]);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet =  __SRE_HwiEnable(g_uwHwiNum);
    //ICUNIT_GOTO_EQUAL(uwRet, OS_SUCCESS, uwRet, EXIT);

    /*激活软中断*/
    g_uwSwiTrigTime = 0;
    g_uwHwiTrigTime = 0;

    uwRet = __SRE_SwiActivate(auwSwiID[1]);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 2, g_uwSwiTrigTime, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwHwiTrigTime, 2, g_uwHwiTrigTime, EXIT);
EXIT:
    if (0xff != auwSwiID[0]) (void)__SRE_SwiDelete(auwSwiID[0]);
    if (0xff != auwSwiID[1]) (void)__SRE_SwiDelete(auwSwiID[1]);
    (void)__SRE_HwiDelete(g_uwHwiNum);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_019
*-@tspec  激活软中断
*-@ttitle 重复激活软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_019()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    UINT16 usSwiLevel = 0xff;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_019_A";
    stInitPara.usPriority = 8;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);  //A
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usSwiLevel = __SRE_SwiDisable();  /*关软中断*/

    /*重复激活软中断*/
    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    __SRE_SwiEnable(usSwiLevel);    /*开软中断*/
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);

EXIT:
    if (0xff != uwSwiID) (void)__SRE_SwiDelete(uwSwiID);
    if (0xff != usSwiLevel) __SRE_SwiEnable(usSwiLevel);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_020
*-@tspec  激活软中断
*-@ttitle 1) 创建两个同优先级的软中断，
          2) 删除其中一个软中断
          3) 激活剩下的软中断，激活正常
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_020()
{
    UINT32 uwRet;
    SWI_HANDLE_T auwSwiID[2] = {0xff, 0xff};
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_020_A";
    stInitPara.usPriority = 8;
    stInitPara.pfnHandler = Hook_SwI_Get_Self_PID;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);  //A
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_020_B";
    stInitPara.usPriority = 8;
    stInitPara.pfnHandler = Hook_SwI_Get_Self_PID;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);  //B
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    /*删除其中一个软中断*/
    uwRet = __SRE_SwiDelete(auwSwiID[0]);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    auwSwiID[0] = 0xff;

    /*激活剩下的软中断*/
    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(auwSwiID[1]);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[0], auwSwiID[1], g_auwSwiPid[0], EXIT);
EXIT:
    if (0xff != auwSwiID[0]) (void)__SRE_SwiDelete(auwSwiID[0]);
    if (0xff != auwSwiID[1]) (void)__SRE_SwiDelete(auwSwiID[1]);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_021
*-@tspec  激活软中断
*-@ttitle 1) 创建一个最高优先级的软中断, 两个普通优先级的软中断
          2) 关软中断的情况下, 激活全部软中断
          3) 删除两个普通优先级的软中断
          4) 开软中断, 最高优先级的软中断能被正常激活
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_021()
{
    UINT32 uwRet;
    SWI_HANDLE_T auwSwiID[3] = {0xff, 0xff, 0xff};
    UINT16 usSwiLevel = 0xff;
    UINT32 i;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_021_high";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    /*创建一个最高优先级的软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);  //high
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_021_A";
    stInitPara.usPriority = 8;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    /*创建两个普通优先级的软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);  //A
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "ut_swi_021_B";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&auwSwiID[2], &stInitPara);  //B
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usSwiLevel = __SRE_SwiDisable();  /*关软中断*/

    /*激活全部软中断*/
    g_uwSwiTrigTime = 0;
    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        uwRet = __SRE_SwiActivate(auwSwiID[i]);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    }

    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 0, g_uwSwiTrigTime, EXIT);

    /*删除两个普通优先级的软中断*/
    uwRet = __SRE_SwiDelete(auwSwiID[1]);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    auwSwiID[1] = 0xff;
    uwRet = __SRE_SwiDelete(auwSwiID[2]);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    auwSwiID[2] = 0xff;

    __SRE_SwiEnable(usSwiLevel);    /*开软中断*/
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);

EXIT:
    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        if (0xff != auwSwiID[i]) (void)__SRE_SwiDelete(auwSwiID[i]);
    }
    if (usSwiLevel != 0xff) __SRE_SwiEnable(usSwiLevel); //开软中断
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_022
*-@tspec  重复激活软中断
*-@ttitle 1) 创建一个软中断
          2) 反复激活创建的软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiActivate_022()
{
    UINT32 uwRet;
    UINT16 usSwiLevel = 0xff;
    UINT32 i;
    UINT32 uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_022_high";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);  //high
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;
    for (i = 0; i < 0x100; i++)
    {
        uwRet = __SRE_SwiActivate(uwSwiID);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    }
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 0x100, g_uwSwiTrigTime, EXIT);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_023
*-@tspec  重复激活软中断
*-@ttitle 1) 创建一个软中断
          2) 反复激活创建的软中断
*/
OS_SEC_TEXT_UT VOID UT_SwiActivate_023_f01(uwArg)
{
    UINT32 i;
    UINT32 uwSwiID;
    UINT32 uwRet;

    for (i = 0; i < 0x100; i++)
    {
        uwRet = __SRE_SwiActivate(uwArg);
        ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
    }

}

OS_SEC_TEXT_UT UINT32 UT_SwiActivate_023()
{
    UINT32 uwRet;
    UINT16 usSwiLevel = 0xff;
    UINT32 uwSwiID;
    UINTPTR uvIntSave;
    UINT32 uwHwiNum = 7;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_022_high";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);  //high
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    //uwRet = SRE_HwiSetAttr(uwHwiNum, 6, OS_HWI_MODE_ENGROSS);
    //ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;

    uwRet = __SRE_HwiCreate(uwHwiNum, 0xa0,IT_HWI_SECURE_MODE,UT_SwiActivate_023_f01, uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    (VOID)__SRE_HwiEnable(uwHwiNum);

	__SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), uwHwiNum);

    uwRet = __SRE_HwiDelete(uwHwiNum);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);


    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_024
*-@tspec  在软中断中重复激活软中断
*-@ttitle 1) 创建一个软中断
          2) 反复激活创建的软中断
*/
OS_SEC_TEXT_UT void UT_SwiActivate_024_f01()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    UINT32 i;

    uwRet = __SRE_SwiSelf(&uwSwiID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    if(g_uwSwiTrigTime < 3)
    {
        for (i = 0; i < 0x50; i++)
        {
            uwRet = __SRE_SwiActivate(uwSwiID);
            ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
        }
    }
    g_uwSwiTrigTime++;
}

OS_SEC_TEXT_UT UINT32 UT_SwiActivate_024()
{
    UINT32 uwRet;
    UINT16 usSwiLevel = 0xff;
    UINT32 i;
    UINT32 uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_024";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = UT_SwiActivate_024_f01;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 4, g_uwSwiTrigTime, EXIT);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test   UT_SwiActivate_025
*-@tspec  激活软中断
*-@ttitle 1) 创建一个最高优先级的软中断, 两个普通优先级的软中断
          2) 关软中断的情况下, 激活全部软中断
          3) 删除两个普通优先级的软中断
          4) 开软中断, 最高优先级的软中断能被正常激活
*/
OS_SEC_TEXT_UT VOID UT_SwiActivate_025_f01()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    UINT16 usSwiPriorityLevel;
    UINT32 i;
    SWI_HANDLE_T auwSwiID[5] = {0xff, 0xff, 0xff, 0xff, 0xff};
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_025_A";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    /*创建一个最高优先级的软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);  //A
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_swi_025_B";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    /*创建两个普通优先级的软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);  //B
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_swi_025_C";
    stInitPara.usPriority = 1;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    /*创建两个普通优先级的软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[2], &stInitPara);  //C
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_swi_025_D";
    stInitPara.usPriority = 2;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&auwSwiID[3], &stInitPara);  //D
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_swi_025_E";
    stInitPara.usPriority = 3;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&auwSwiID[4], &stInitPara);  //E
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    usSwiPriorityLevel = __SRE_SwiDisable();
    ICUNIT_ASSERT_EQUAL_VOID(usSwiPriorityLevel, g_usSwiPriorityLevel, usSwiPriorityLevel);

    /*激活全部软中断*/
    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        uwRet = __SRE_SwiActivate(auwSwiID[i]);
        ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
    }
    ICUNIT_ASSERT_EQUAL_VOID(g_uwSwiTrigTime, 0, g_uwSwiTrigTime);

    __SRE_SwiEnable(usSwiPriorityLevel);    /*开软中断*/
    ICUNIT_ASSERT_EQUAL_VOID(g_uwSwiTrigTime, 3, g_uwSwiTrigTime);

    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        if (0xff != auwSwiID[i]) (void)__SRE_SwiDelete(auwSwiID[i]);
    }

}

OS_SEC_TEXT_UT UINT32 UT_SwiActivate_025()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_act_025";
    stInitPara.usPriority = 2;
    stInitPara.pfnHandler = UT_SwiActivate_025_f01;
    stInitPara.uwInitValue = 0;

    /*创建一个最高优先级的软中断*/
    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test   UT_osSwiRdyPop_001
*-@tspec  取出最高优先级的READY软中断
*-@ttitle READY队列中的最高优先级低于指定优先级
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiRdyPop_001()
{
    UINT32 uwRet;
    UINTPTR uvIntSave;
    UINT32 uwSwiPrio;
    SWI_ATTRIBUTE_S *pstSwiAttr;

    uvIntSave = __SRE_IntLock();
    uwSwiPrio = osGetLMB1(g_vuwSwiRdy);
    pstSwiAttr = osSwiRdyPop(uwSwiPrio+1);
    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(pstSwiAttr, NULL, pstSwiAttr);

    return SRE_OK;
}

/**
*-@test   UT_osSwiRdyPop_002
*-@tspec  取出最高优先级的READY软中断
*-@ttitle READY队列中的最高优先级等于软中断触发级别
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiRdyPop_002()
{
    UINT32 uwRet;
    UINTPTR uvIntSave;
    UINT32 uwSwiPrio;
    SWI_ATTRIBUTE_S *pstSwiAttr;

    uvIntSave = __SRE_IntLock();
    uwSwiPrio = g_usSwiPriorityLevel;
    pstSwiAttr = osSwiRdyPop(uwSwiPrio);
    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(pstSwiAttr, NULL, pstSwiAttr);

    return SRE_OK;
}

/**
*-@test   UT_osSwiRdyPop_003
*-@tspec  取出最高优先级的READY软中断
*-@ttitle READY队列中的最高优先级低于软中断触发级别
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiRdyPop_003()
{
    UINT32 uwRet;
    UINTPTR uvIntSave;
    UINT32 uwSwiPrio;
    SWI_ATTRIBUTE_S *pstSwiAttr;

    uvIntSave = __SRE_IntLock();
    uwSwiPrio = g_usSwiPriorityLevel;
    pstSwiAttr = osSwiRdyPop(uwSwiPrio+1);
    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(pstSwiAttr, NULL, pstSwiAttr);

    return SRE_OK;
}

/**
*-@test   UT_osSwiRdyPop_004
*-@tspec  取出最高优先级的READY软中断
*-@ttitle READY队列中的最高优先级等于指定优先级
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiRdyPop_004()
{
    UINT32 uwRet;
    UINTPTR uvIntSave;
    UINT32 uwSwiPrio;
    SWI_ATTRIBUTE_S *pstSwiAttr;

    uvIntSave = __SRE_IntLock();
    uwSwiPrio = osGetLMB1(g_vuwSwiRdy);
    pstSwiAttr = osSwiRdyPop(uwSwiPrio);
    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(pstSwiAttr, NULL, pstSwiAttr);

    return SRE_OK;
}

/**
*-@test   UT_osSwiRdyPop_005
*-@tspec  取出最高优先级的READY软中断
*-@ttitle 取出READY队列中的最高优先级软中断成功
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiRdyPop_005()
{
    UINT32 uwRet;
    UINTPTR uvIntSave;
    UINT32 uwSwiPrio = 0;
    UINT32 uwSwiPrio2 = 1;
    UINT32 i;
    UINT16 usSwiPriorityLevel;
    UINT32 auwSwiID[3] = {0xff, 0xff, 0xff};
    SWI_ATTRIBUTE_S *pstSwiAttr1;
    SWI_ATTRIBUTE_S *pstSwiAttr2;
    SWI_ATTRIBUTE_S *pstSwiAttr3;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_SwiPop_005_A";
    stInitPara.usPriority = uwSwiPrio;
    stInitPara.pfnHandler = Hook_SwI_Get_Self_PID;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);  //A
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_SwiPop_005_B";
    stInitPara.usPriority = uwSwiPrio;
    stInitPara.pfnHandler = Hook_SwI_Get_Self_PID;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);  //B
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "ut_SwiPop_005_C";
    stInitPara.usPriority = uwSwiPrio2;
    stInitPara.pfnHandler = Hook_SwI_Get_Self_PID;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&auwSwiID[2], &stInitPara);  //C
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usSwiPriorityLevel = __SRE_SwiDisable();
    ICUNIT_ASSERT_EQUAL(usSwiPriorityLevel, g_usSwiPriorityLevel, usSwiPriorityLevel);

    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        uwRet = __SRE_SwiActivate(auwSwiID[i]);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }

    uvIntSave = __SRE_IntLock();
    pstSwiAttr1 = osSwiRdyPop(uwSwiPrio + 1);
    pstSwiAttr2 = osSwiRdyPop(uwSwiPrio + 1);
    pstSwiAttr3 = osSwiRdyPop(uwSwiPrio2 + 1);

    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(pstSwiAttr1, GET_SCB_HANDLE(auwSwiID[0]), pstSwiAttr1);
    ICUNIT_ASSERT_EQUAL(pstSwiAttr2, GET_SCB_HANDLE(auwSwiID[1]), pstSwiAttr2);
    ICUNIT_ASSERT_EQUAL(pstSwiAttr3, GET_SCB_HANDLE(auwSwiID[2]), pstSwiAttr3);

    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        uwRet = __SRE_SwiDelete(auwSwiID[i]);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }

    __SRE_SwiEnable(usSwiPriorityLevel);

    return SRE_OK;
}

/**
*-@test   UT_SwiDisable_001
*-@tspec  去使能软中断
*-@ttitle 背景线程未启动, 去使能失败
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDisable_001()
{
    UINT32  uwRet;
    UINTPTR uvIntSave;
    UINT32  uwUniFlagTmp;
    UINT32  uwSwiID;
    UINT16 usSwiPriorityLevel;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_Dis_01";
    stInitPara.usPriority = 0;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    uvIntSave = __SRE_IntUnLock();

    uwUniFlagTmp = g_vuwUniFlag;

    g_vuwUniFlag &= (~OS_FLG_BGD_ACTIVE);

    usSwiPriorityLevel = __SRE_SwiDisable();
    ICUNIT_ASSERT_EQUAL(usSwiPriorityLevel, g_usSwiPriorityLevel, usSwiPriorityLevel);

    g_vuwUniFlag = uwUniFlagTmp;

    __SRE_IntRestore(uvIntSave);

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    g_uwSwiTrigTime = 0;

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime);

    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test   UT_SwiDisable_002
*-@tspec  去使能软中断
*-@ttitle 去使能软中断成功
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDisable_002()
{
    UINT32  uwRet;
    UINTPTR uvIntSave;
    UINT32  uwSwiID;
    SWI_ATTRIBUTE_S *pstSwiCB;
    UINT16  usStatusFlag;
    UINT16 usSwiPriorityLevel;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_Dis_02";
    stInitPara.usPriority = 1;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    usSwiPriorityLevel = __SRE_SwiDisable();
    ICUNIT_ASSERT_EQUAL(usSwiPriorityLevel, g_usSwiPriorityLevel, usSwiPriorityLevel);

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    g_uwSwiTrigTime = 0;

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    pstSwiCB = GET_SCB_HANDLE(uwSwiID);

    usStatusFlag = (pstSwiCB->usStatus) & OS_SWI_READY;

    ICUNIT_ASSERT_NOT_EQUAL(usStatusFlag, 0, usStatusFlag);
    ICUNIT_ASSERT_EQUAL(g_uwSwiTrigTime, 0, g_uwSwiTrigTime);

    __SRE_SwiEnable(usSwiPriorityLevel);

    ICUNIT_ASSERT_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime);

    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test   UT_SwiEnable_001
*-@tspec  使能指定级别以上（不包含指定级别）的软中断
*-@ttitle 优先级超出范围, 使能失败
*/
OS_SEC_TEXT_UT UINT32 UT_SwiEnable_001()
{
    UINT32 uwRet;
    UINT32 usSwiPriorityLevel;

    usSwiPriorityLevel = g_usSwiPriorityLevel;
    __SRE_SwiEnable(OS_SWI_PRIORITY_ALL+1);
    ICUNIT_ASSERT_EQUAL(g_usSwiPriorityLevel, usSwiPriorityLevel, g_usSwiPriorityLevel);

    return SRE_OK;
}

/**
*-@test   UT_SwiEnable_002
*-@tspec  使能指定级别以上（不包含指定级别）的软中断
*-@ttitle 背景线程未启动, 使能失败
*/
OS_SEC_TEXT_UT UINT32 UT_SwiEnable_002()
{
    UINT32  uwRet;
    UINT32  usSwiPriorityLevel;
    UINT32  uwUniFlag;
    UINTPTR uvIntSave;

    uvIntSave = __SRE_IntLock();
    uwUniFlag = g_vuwUniFlag;
    g_vuwUniFlag &= ~OS_FLG_BGD_ACTIVE;
    usSwiPriorityLevel = g_usSwiPriorityLevel;
    __SRE_SwiEnable(OS_SWI_PRIORITY_ALL);
    g_vuwUniFlag = uwUniFlag;
    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(g_usSwiPriorityLevel, usSwiPriorityLevel, g_usSwiPriorityLevel);

    return SRE_OK;
}

/**
*-@test   UT_SwiEnable_003
*-@tspec  使能指定级别以上（不包含指定级别）的软中断
*-@ttitle Disable软中断的情况下，Enable指定级别以上的软中断，
          高于该优先级且就绪的软中断能被激活运行, 等于或低于该优先级的软中断不能被激活运行
*/
OS_SEC_TEXT_UT UINT32 UT_SwiEnable_003()
{
    UINT32  uwRet;
    UINT32  usPrioLvl = 0xff;
    UINT32  auwSwiID[3] = {0xff, 0xff, 0xff};
    UINT16  usPrio = 5;
    UINT32  i;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "swi_ena03_high";
    stInitPara.usPriority = usPrio;
    stInitPara.pfnHandler = Hook_SwI_Get_Self_PID;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "swi_ena03_mid";
    stInitPara.usPriority = usPrio + 1;
    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "swi_ena03_low";
    stInitPara.usPriority = usPrio + 2;
    uwRet = __SRE_SwiCreate(&auwSwiID[2], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usPrioLvl = __SRE_SwiDisable();

    g_uwSwiTrigTime = 0;
    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        g_auwSwiPid[i] = 0xff;
        uwRet = __SRE_SwiActivate(auwSwiID[i]); //激活软中断，进入就绪队列，但不会被响应
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    }
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 0, g_uwSwiTrigTime, EXIT);

    __SRE_SwiEnable(usPrio+1); //Enable后，软中断auwSwiID[0]被响应, auwSwiID[1], auwSwiID[2]不被响应
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime, EXIT);
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[0], auwSwiID[0], g_auwSwiPid[0], EXIT);
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[1], 0xff, g_auwSwiPid[1], EXIT);
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[2], 0xff, g_auwSwiPid[2], EXIT);
EXIT:
    for (i = 0; i < sizeof(auwSwiID)/sizeof(auwSwiID[0]); i++)
    {
        if (auwSwiID[i] != 0xff) (void)__SRE_SwiDelete(auwSwiID[i]);
    }

    if (0xff != usPrioLvl) (void)__SRE_SwiEnable(usPrioLvl); //恢复软中断触发级别
    return SRE_OK;
}

/**
*-@test   UT_SwiEnable_004
*-@tspec  使能指定级别以上（不包含指定级别）的软中断
*-@ttitle
1) 创建低优先级软中断，在低优先级中断里Disable软中断，激活高优先级中断，高优先级中断不被响应
2) Enable软中断，高优先级软中断抢占低优先级软中断
*/
OS_SEC_TEXT_UT VOID UT_Hook_SwiEnable_004(UINT32 uwArg)
{
    UINT32 usSwiPrioLvl;
    SWI_INFO_S stSwiInfo;

    usSwiPrioLvl = __SRE_SwiDisable();
    (void)__SRE_SwiActivate(uwArg); //激活后，高优先级软中断不被响应
    ICUNIT_TRACK_EQUAL(g_uwSwiTrigTime, 0, g_uwSwiTrigTime);
    (void)SRE_SwiInfoGet(uwArg, &stSwiInfo);
    __SRE_SwiEnable(stSwiInfo.usPriority+1);  //Enable后，高优先级软中断抢占低优先级软中断
    ICUNIT_TRACK_EQUAL(g_uwSwiTrigTime, 1, g_uwSwiTrigTime);
    g_uwSwiTrigTime++;
    __SRE_SwiEnable(usSwiPrioLvl); //恢复原软中断触发级别
}

OS_SEC_TEXT_UT UINT32 UT_SwiEnable_004()
{
    UINT32  uwRet;
    UINT32  uwUniFlag;
    UINTPTR uvIntSave;
    UINT32  auwSwiID[2] = {0xff, 0xff};
    UINT16  usPrio = 5;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "swi_ena04_high";
    stInitPara.usPriority = usPrio;
    stInitPara.pfnHandler = Hook_Swi_TrigTime_Inc;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "swi_ena04_low";
    stInitPara.usPriority = usPrio + 1;
    stInitPara.pfnHandler = UT_Hook_SwiEnable_004;
    stInitPara.uwInitValue = auwSwiID[0];

    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    g_uwSwiTrigTime = 0;
    uwRet = __SRE_SwiActivate(auwSwiID[1]); //激活低优先级软中断
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime, 2, g_uwSwiTrigTime, EXIT);  //两个软中断都应被响应

EXIT:
    if (auwSwiID[0] != 0xff) (void)__SRE_SwiDelete(auwSwiID[0]);
    if (auwSwiID[1] != 0xff) (void)__SRE_SwiDelete(auwSwiID[1]);
    return SRE_OK;
}

/**
*-@test   UT_osSwiReadyDel_001
*-@tspec  删除就绪软中断
*-@ttitle 1)创建5个软中断A,B,C,D,E, 优先级为A>B=C=D>E;
          2)Disable软中断
          3)激活5个软中断
          4)删除软中断B,C,D
          4)Enable软中断, 软中断HOOK被执行的顺序应该是A,E
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiReadyDel_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T auwSwiID[5] = {0xff, 0xff, 0xff, 0xff, 0xff};
    SWI_PRIOR_T usPriorLow = 7;
    UINT16 usPrioLvl = 0xff;
    UINT32 i;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "swi_rd01_A";
    stInitPara.usPriority = usPriorLow - 2;
    stInitPara.pfnHandler = Hook_SwI_Get_Self_PID;
    stInitPara.uwInitValue = 0;

    /*创建4个软中断A,B,C,D*/
    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara); //Swi_high
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitPara.pcSwiName  = "swi_rd01_B";
    stInitPara.usPriority = usPriorLow - 1;
    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara); //Swi_mid_01
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "swi_rd01_C";
    uwRet = __SRE_SwiCreate(&auwSwiID[2], &stInitPara); //Swi_mid_02
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "swi_rd01_D";
    uwRet = __SRE_SwiCreate(&auwSwiID[3], &stInitPara); //Swi_mid_03
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    stInitPara.pcSwiName  = "swi_rd01_E";
    stInitPara.usPriority = usPriorLow;
    uwRet = __SRE_SwiCreate(&auwSwiID[4], &stInitPara);   //Swi_low_02
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    /*关闭软中断*/
    usPrioLvl = __SRE_SwiDisable();

    /*激活软中断*/
    for (i = 0; i < 5; i++)
    {
        uwRet = __SRE_SwiActivate(auwSwiID[i]);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    }

    /*删除软中断B,C,D*/
    for (i = 1; i <= 3; i++)
    {
        uwRet = __SRE_SwiDelete(auwSwiID[i]);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
        auwSwiID[i] = 0xff;
    }

    /*打开软中断*/
    for (i = 0; i < 5; i++)
    {
        g_auwSwiPid[i] = 0xff;
    }
    g_uwSwiTrigTime = 0;
    __SRE_SwiEnable(usPriorLow+1);

    /*CHECK*/
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[0], auwSwiID[0], g_auwSwiPid[0], EXIT);  //A
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[1], auwSwiID[4], g_auwSwiPid[1], EXIT);  //E
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[2], 0xff, g_auwSwiPid[2], EXIT);
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[3], 0xff, g_auwSwiPid[3], EXIT);
    ICUNIT_GOTO_EQUAL(g_auwSwiPid[4], 0xff, g_auwSwiPid[2], EXIT);

EXIT:
    for (i = 0; i < 5; i++)
    {
        if (0xff != auwSwiID[i]) (void)__SRE_SwiDelete(auwSwiID[i]);
    }
    if (0xff != usPrioLvl) __SRE_SwiEnable(usPrioLvl); //恢复软中断原触发级别
    return SRE_OK;
}

/**
*-@test   UT_osGetLMB1
*-@tspec  获取位图中的优先级
*-@ttitle 1)位图为0时，优先级应返回32
          2)位图为0x8$$$$$$$$时，优先级应返回0
          3)位图为0x008$$$$$$时，优先级应返回8
*/
OS_SEC_TEXT_UT UINT32 UT_osGetLMB1()
{
    UINTPTR uwPriority = 0xff;

    uwPriority = osGetLMB1(0x0);
    ICUNIT_ASSERT_EQUAL(uwPriority, 32, uwPriority);

    uwPriority = osGetLMB1(0x80003f74);
    ICUNIT_ASSERT_EQUAL(uwPriority, 0, uwPriority);

    uwPriority = osGetLMB1(0x00803f74);
    ICUNIT_ASSERT_EQUAL(uwPriority, 8, uwPriority);

    return SRE_OK;
}

/**
*-@test UT_osSwiIdlBGD_001
*-@tspec
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
VOID UT_osSwiIdlBGD_001_f02()
{
    UINT32 uwTaskID;
    UINT32 uwRet;
    m_uwSwiTest ++;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
    __SRE_TaskSuspend(uwTaskID);
}

VOID UT_osSwiIdlBGD_001_f03()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    osSwiIdlBGD();

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_osSwiIdlBGD_001()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;
    OS_IDLE_HOOK m_pfnSysIdlePrefixHookTemp;

    m_pfnSysIdlePrefixHookTemp = m_pfnSysIdlePrefixHook;


    m_pfnSysIdlePrefixHook = UT_osSwiIdlBGD_001_f02;
    m_uwSwiTest = 0;


    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_osSwiIdlBGD_001_f03;
    stInitParam.usTaskPrio   = 24;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);


    ICUNIT_GOTO_EQUAL(m_uwSwiTest, 1, m_uwSwiTest, EXIT);

EXIT:
    __SRE_TaskDelete(uwTaskID);

    m_pfnSysIdlePrefixHook = m_pfnSysIdlePrefixHookTemp;

    return SRE_OK;
}

#if 0
/**
*-@test UT_osMcSwiActNullHandler_001
*-@tspec
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osMcSwiActNullHandler_001()
{
    UINT32 uwRet;

    uwRet = osMcSwiActNullHandler(0, 0, 0);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_MC_INT_FAIL, uwRet);

    return SRE_OK;
}
#endif
#if  (OS_HAVE_COPROCESSOR1 == YES)
/**
*-@test   UT_swiTrigHwi
*-@tspec  软中断触发硬中断,硬中断返回软中断后,cpenable保持嵌套前的值不变
*-@ttitle
*/
OS_SEC_TEXT_UT VOID UT_swiTrigHwi_001_f01(UINT32 uwArg)
{
    UINT32 uwRet;
    volatile UINT32 uwCnt = 1000;
    UINTPTR  uvCpEnable;

    SRE_SwiCpEntry();
    g_uwHwiTrigTime = 0;
	__SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), uwArg);

    while (g_uwHwiTrigTime != 1)
    {
        uwCnt--; //延时,确保硬中断触发
    }

    __asm__ __volatile__( "rsr %0, cpenable" : "=a" (uvCpEnable) );
    ICUNIT_ASSERT_EQUAL_VOID(uvCpEnable, 0x2, uvCpEnable);

    SRE_SwiCpExit();
}

OS_SEC_TEXT_UT UINT32 UT_swiTrigHwi_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    UINT32 uwHwiNo = 7;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "Swi_Nest";
    stInitPara.usPriority = 5;
    stInitPara.pfnHandler = UT_swiTrigHwi_001_f01;
    stInitPara.uwInitValue = uwHwiNo;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    //SRE_HwiSetAttr(uwHwiNo, 3, OS_HWI_MODE_ENGROSS);

    /*创建使能硬中断*/
    uwRet = __SRE_HwiCreate(uwHwiNo,0xa0,IT_HWI_SECURE_MODE,Hook_Hwi_TrigTime_Inc, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    __SRE_HwiEnable(uwHwiNo);

    /*激活软中断*/
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
EXIT:
    if (0xff != uwSwiID)
    {
        __SRE_SwiDelete(uwSwiID);
    }
    (VOID)__SRE_HwiDelete(uwHwiNo);

    return SRE_OK;
}
#endif

OS_SEC_TEXT_UT VOID UT_sre_swi()
{
    UINT32 uiSuiteId;
    TEST_ADD_SUITE(uiSuiteId, "UT_sre_Swi");
    //TEST_ADD_CASE(UT_SwiActivate_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SwiActivate_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_010, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_011, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_012, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_013, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_014, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_015, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_016, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_017, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_018, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_019, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_020, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_021, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_022, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_023, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_024, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiActivate_025, uiSuiteId, Label_RUN);


    TEST_ADD_CASE(UT_osSwiRdyPop_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osSwiRdyPop_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osSwiRdyPop_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osSwiRdyPop_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osSwiRdyPop_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDisable_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDisable_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiEnable_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiEnable_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiEnable_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiEnable_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osSwiReadyDel_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_osGetLMB1, uiSuiteId, Label_RUN);
#if  (OS_HAVE_COPROCESSOR1 == YES)
    TEST_ADD_CASE(UT_swiTrigHwi_001, uiSuiteId, Label_RUN);
#endif

    TEST_ADD_CASE(UT_osSwiIdlBGD_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_osMcSwiActNullHandler_001, uiSuiteId, Label_RUN);

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            










                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               