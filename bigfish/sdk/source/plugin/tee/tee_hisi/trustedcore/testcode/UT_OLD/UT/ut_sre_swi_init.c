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
#include "sre_task.ph"
#include "sre_base.h"
#include "sre_hw.ph"
#include "Set_Peg.h"
#include "sre_sys.h"
#include "sre_sys.ph"
#include "sre_mem.h"
#include "sre_hunt.h"
//#include "sre_tick.h"
//#include "sre_err.ph"
#include "Set_Peg.h"
#include "iCunit.h"
//#include <string.h>
#include "osTest.h"
#include "sre_buildef.h"
#include "app_data_common.h"

//EXTERN_FAR SWI_HANDLE_T         g_uwTickSwiID;
extern SWI_HANDLE_T  g_uwIdleSwiID;

extern UINT32 osSwiInit(VOID);
extern UINT32 osSwiRegister(SWI_MOD_INFO_S *pstModInfo);

extern UINT16 g_usSwiMaxNum;
extern UINT32 g_uwTskMaxNum;
extern LIST_OBJECT_S  g_stSwiFreeList;
//extern TICK_MOD_INFO_S m_stTickModInfo;
extern TST_CDA_INFO_S *g_pstCdaInfoAddr;


OS_SEC_TEXT_UT VOID * SRE_MemAllocAlign_SWI_001(UINT32 uwMid, UINT8 ucPtNo, UINT32 uwSize, OS_MEM_ALIGN_E enAlignPow)
{
    return NULL;
}

OS_SEC_TEXT_UT VOID UT_Swi_Func_init_001(UINT32 uwArg)
{
;
}

OS_SEC_TEXT_UT VOID UT_Swi_Func_init_002(UINT32 uwArg)
{
;
}

/**
*-@test  UT_osSwiRegister_001
*-@tspec 软中断配置数目
*-@ttitle软中断配置的最大支持数不合适
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiRegister_001()
{
    UINT32 uwRet;
    SWI_MOD_INFO_S  stModInfo;
    stModInfo.uwMaxNum = SWI_MAX_CFG_NUM + 1;
    uwRet = osSwiRegister(&stModInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_MAX_NUM_NOT_SUITED, uwRet);

    return SRE_OK;
}
#if 0
/**
*-@test  UT_osSwiInit_001
*-@tspec 软中断初始化
*-@ttitle申请内存失败。
*-@caution 对全局变量的影响太大, 不建议测试
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiInit_001()
{
    UINT32 uwRet;
    SETPEG_JMP_ST stIncSave;
    UINT32 g_uwTskMaxNumTemp;
    TICK_MOD_INFO_S m_stTickModInfoTemp;
    UINT32 m_uwLmPidNumTemp;
    UINT32 g_uwThreadNumTemp;
    UINT16 g_usSwiMaxNumTemp;
    UINT32 g_vuwUniFlagTemp;
    UINT32 g_vuwSwiRdyTemp;
    SWI_ATTRIBUTE_S  *g_pstSwiActiveTemp;
    SWI_LIST_S        g_stSwiDataTemp;
    TST_CDA_INFO_S    g_stCdaInfoAddrTemp;

    g_uwTskMaxNumTemp = g_uwTskMaxNum;
    m_stTickModInfoTemp.uwTickPerSecond = m_stTickModInfo.uwTickPerSecond;
    g_uwThreadNumTemp = g_uwThreadNum;
    g_usSwiMaxNumTemp = g_usSwiMaxNum;
    g_vuwUniFlagTemp  = g_vuwUniFlag;
    g_vuwSwiRdyTemp   = g_vuwSwiRdy;
    g_pstSwiActiveTemp = g_pstSwiActive;
    g_stSwiDataTemp.pstList = g_stSwiData.pstList;
    g_stCdaInfoAddrTemp.uwSwiMaxNum    = g_pstCdaInfoAddr->uwSwiMaxNum;
    g_stCdaInfoAddrTemp.uwSCBStartAddr = g_pstCdaInfoAddr->uwSCBStartAddr;

    g_usSwiMaxNum = 0;
    m_stTickModInfo.uwTickPerSecond = 0;

    uwRet = osSwiInit();
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(g_usSwiMaxNum, 0, g_usSwiMaxNum);
    ICUNIT_ASSERT_EQUAL(g_pstSwiActive, NULL, g_pstSwiActive);

    g_uwTskMaxNum = g_uwTskMaxNumTemp;
    m_stTickModInfo.uwTickPerSecond = m_stTickModInfoTemp.uwTickPerSecond;
    g_uwThreadNum = g_uwThreadNumTemp;
    g_usSwiMaxNum = g_usSwiMaxNumTemp;
    g_vuwUniFlag  = g_vuwUniFlagTemp;
    g_vuwSwiRdy   = g_vuwSwiRdyTemp;
    g_pstSwiActive = g_pstSwiActiveTemp;
    g_stSwiData.pstList = g_stSwiDataTemp.pstList;
    g_pstCdaInfoAddr->uwSwiMaxNum    = g_stCdaInfoAddrTemp.uwSwiMaxNum;
    g_pstCdaInfoAddr->uwSCBStartAddr = g_stCdaInfoAddrTemp.uwSCBStartAddr;

    return SRE_OK;
}


/**
*-@test  UT_osSwiInit_002
*-@tspec 软中断初始化
*-@ttitle申请内存失败。
*-@caution 对全局变量的影响太大, 不建议测试
*/
OS_SEC_TEXT_UT UINT32 UT_osSwiInit_002()
{
    UINT32 uwRet;
    SETPEG_JMP_ST stIncSave;

    SET_PEG(SRE_MemAllocAlign, SRE_MemAllocAlign_SWI_001, &stIncSave);

    uwRet = osSwiInit();

    CLEAN_PEG(SRE_MemAllocAlign, stIncSave);

    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_NO_MEMORY, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_osSwiActivate_001
*-@tspec 软中断初始化
*-@ttitle
*-@caution
*/
VOID UT_osSwiActivate_001_uniErrHandle(CHAR *pcFileName, UINT32 uwLineNo, UINT32 uwErrorNo, UINT32 uwParaLen, VOID  *pPara)
{
    return;
}

OS_SEC_TEXT_UT UINT32 UT_osSwiActivate_001()
{
    UINT32 uwRet;
    SETPEG_JMP_ST stIncSave;
    UINTPTR uvIntSave;
    SWI_PROC_FUNC        g_pfnSwiIdleEntryTemp;
    g_pfnSwiIdleEntryTemp = g_pfnSwiIdleEntry;

    uvIntSave = __SRE_IntLock();

    g_pfnSwiIdleEntry = NULL;

    SET_PEG(SRE_ErrHandle, UT_osSwiActivate_001_uniErrHandle, (SETPEG_JMP_ST *)&stIncSave);

    uwRet = osSwiActivate();
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_BGD_CREATE_FAIL, uwRet);

    CLEAN_PEG(SRE_ErrHandle, stIncSave);

    g_pfnSwiIdleEntry = g_pfnSwiIdleEntryTemp;

    __SRE_IntRestore(uvIntSave);

    return SRE_OK;
}
#endif
/**
*-@test  UT_SwiCreate_001
*-@tspec 创建软中断
*-@ttitle软中断优先级非法
*/
OS_SEC_TEXT_UT UINT32 UT_SwiCreate_001()
{
    UINT32       uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_001";
    stInitPara.usPriority = OS_SWI_PRIORITY_LOWEST + 1;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);

    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SWI_PRIORITY_INVALID, uwRet,EXIT);
EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    return SRE_OK;

}

/**
*-@test  UT_SwiCreate_002
*-@tspec 创建软中断
*-@ttitle软中断处理函数为空
*/
OS_SEC_TEXT_UT UINT32 UT_SwiCreate_002()
{
    UINT32       uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_002";
    stInitPara.usPriority = OS_SWI_PRIORITY_LOWEST;
    stInitPara.pfnHandler = NULL;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);

    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SWI_PROC_FUNC_NULL, uwRet,EXIT);
EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    return SRE_OK;

}

/**
*-@test  UT_SwiCreate_003
*-@tspec 创建软中断
*-@ttitle指针参数为空。
*/
OS_SEC_TEXT_UT UINT32 UT_SwiCreate_003()
{
    UINT32       uwRet;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_003";
    stInitPara.usPriority = OS_SWI_PRIORITY_LOWEST;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;


    uwRet = __SRE_SwiCreate((SWI_HANDLE_T *)NULL, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_PTR_NULL, uwRet);

    return SRE_OK;

}

/**
*-@test  UT_SwiCreate_004
*-@tspec 创建软中断
*-@ttitle软中断名的指针为空
*/
OS_SEC_TEXT_UT UINT32 UT_SwiCreate_004()
{
    UINT32       uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = NULL;
    stInitPara.usPriority = OS_SWI_PRIORITY_LOWEST;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SWI_NAME_EMPTY, uwRet,EXIT);
EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    return SRE_OK;

}

/**
*-@test  UT_SwiCreate_005
*-@tspec 增加软中断
*-@ttitle软中断名为空字符串
*/
OS_SEC_TEXT_UT UINT32 UT_SwiCreate_005()
{
    UINT32       uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SWI_NAME_EMPTY, uwRet,EXIT);
EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    return SRE_OK;
}


/**
*-@test  UT_SwiCreate_006
*-@tspec 增加软中断
*-@ttitle软中断入参结构体指针为NULL
*/
OS_SEC_TEXT_UT UINT32 UT_SwiCreate_006()
{
    UINT32       uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;

    uwRet = __SRE_SwiCreate(&uwSwiID, NULL);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SWI_PTR_NULL, uwRet,EXIT);
EXIT:
    if (uwSwiID < 0xff)
    {
        uwRet = __SRE_SwiDelete(uwSwiID);
    }

    return SRE_OK;
}

/**
*-@test  UT_SwiCreate_007
*-@tspec 增加软中断
*-@ttitle1)创建两个优先级为B的软中断；2)创建另一个优先级为A的软中断，A=0, B>0
*/
OS_SEC_TEXT_UT UINT32 UT_SwiCreate_007()
{
    UINT32       uwRet;
    SWI_HANDLE_T auwSwiID[3]={0xff,0xff,0xff};
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "swi_B_1";
    stInitPara.usPriority = 1;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);

    stInitPara.pcSwiName  = "swi_B_2";
    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);

    stInitPara.pcSwiName  = "swi_A_1";
    stInitPara.usPriority = 0;

    uwRet = __SRE_SwiCreate(&auwSwiID[2], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);

EXIT:
    if (0xff != auwSwiID[0]) (void)__SRE_SwiDelete(auwSwiID[0]);
    if (0xff != auwSwiID[1]) (void)__SRE_SwiDelete(auwSwiID[1]);
    if (0xff != auwSwiID[2]) (void)__SRE_SwiDelete(auwSwiID[2]);
    return SRE_OK;
}

/**
*-@test UT_SwiCreate_008
*-@tspec
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32  UT_SwiCreate_008()
{
    UINT32       uwRet;
    SWI_HANDLE_T auwSwiID[3]={0xff,0xff,0xff};
    LIST_OBJECT_S        g_stSwiFreeListTemp;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "swi_007";
    stInitPara.usPriority = 1;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;

    g_stSwiFreeListTemp.pstNext = g_stSwiFreeList.pstNext;

    g_stSwiFreeList.pstNext = &g_stSwiFreeList;

    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SWI_SCB_USED_OUT, uwRet,EXIT);

    g_stSwiFreeList.pstNext = g_stSwiFreeListTemp.pstNext;

EXIT:
    if (0xff != auwSwiID[0]) (void)__SRE_SwiDelete(auwSwiID[0]);
    return SRE_OK;

}

/**
*-@test UT_SwiCreate_009
*-@tspec
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32  UT_SwiCreate_009()
{
    UINT32       uwRet;
    SWI_HANDLE_T auwSwiID[3]={0xff,0xff,0xff};
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "swi_008_B_1";
    stInitPara.usPriority = 1;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&auwSwiID[0], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);

    uwRet = __SRE_SwiCreate(&auwSwiID[1], &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HUNT_THREAD_NAME_REPEAT, uwRet,EXIT);

EXIT:
    if (0xff != auwSwiID[0]) (void)__SRE_SwiDelete(auwSwiID[0]);
    if (0xff != auwSwiID[1]) (void)__SRE_SwiDelete(auwSwiID[1]);

    return SRE_OK;

}

/**
*-@test UT_SwiCreate_010
*-@tspec
*-@ttitle 创建多个同优先级软中断，并观察其状态
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32  UT_SwiCreate_010()
{
    UINT32       uwRet;
    SWI_HANDLE_T auwSwiID[5]={0xff,0xff,0xff, 0xff,0xff};
    SWI_INIT_PARA_S stInitPara;
    CHAR acSwiName[16] = "Swi_create";
    UINT32 uwLoop;
    SWI_ATTRIBUTE_S *pstSwiCB;

    stInitPara.usPriority = 1;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;

    for (uwLoop = 0; uwLoop < sizeof(auwSwiID)/sizeof(auwSwiID[0]); uwLoop++)
    {
        acSwiName[10] = '0' + uwLoop;
        stInitPara.pcSwiName  = acSwiName;

        uwRet = __SRE_SwiCreate(&auwSwiID[uwLoop], &stInitPara);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

        pstSwiCB = GET_SCB_HANDLE(auwSwiID[uwLoop]);

        ICUNIT_ASSERT_EQUAL(pstSwiCB->usStatus, OS_SWI_CREATED, pstSwiCB->usStatus);
    }

EXIT:
    for (uwLoop = 0; uwLoop < sizeof(auwSwiID)/sizeof(auwSwiID[0]); uwLoop++)
    {
        uwRet = __SRE_SwiDelete(auwSwiID[uwLoop]);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }

    return SRE_OK;

}

/**
*-@test UT_SwiCreate_011
*-@tspec
*-@ttitle 创建多个同优先级软中断，并将其加入到观察其状态
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID  UT_SwiCreate_011_f01(UINT32 uwArg)
{
    UINT32  uwRet;
    SWI_HANDLE_T auwSwiID[3]={0xff,0xff,0xff};
    CHAR acSwiName[12] = "Swi_create";
    UINT32 uwLoop;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.usPriority = 2;
    stInitPara.pfnHandler = UT_Swi_Func_init_001;
    stInitPara.uwInitValue = 0;

    for (uwLoop = 0; uwLoop < sizeof(auwSwiID)/sizeof(auwSwiID[0]); uwLoop++)
    {
        acSwiName[10] = '0' + uwLoop;
        stInitPara.pcSwiName  = acSwiName;

        uwRet = __SRE_SwiCreate(&auwSwiID[uwLoop], &stInitPara);
        ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

        uwRet = __SRE_SwiActivate(auwSwiID[uwLoop]);
        ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
    }

EXIT:
    for (uwLoop = 0; uwLoop < sizeof(auwSwiID)/sizeof(auwSwiID[0]); uwLoop++)
    {
        uwRet = __SRE_SwiDelete(auwSwiID[uwLoop]);
        ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
    }
}

OS_SEC_TEXT_UT UINT32  UT_SwiCreate_011()
{
    UINT32  uwRet;
    SWI_INIT_PARA_S stInitPara;
    UINT32 uwSwiID;
    UINT32 uwLoop;

    stInitPara.usPriority = 1;
    stInitPara.pfnHandler = UT_SwiCreate_011_f01;
    stInitPara.pcSwiName= "Swi_create11";
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SwiDelete_001
*-@tspec 删除软中断
*-@ttitle软中断ID非法。
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDelete_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum);
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SwiDelete_002
*-@tspec 删除软中断
*-@ttitle删除其他核的软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDelete_002()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID()+1, 0);
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SwiDelete_003
*-@tspec 删除软中断
*-@ttitle删除IDLE软中断。
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDelete_003()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;

    uwSwiID = g_uwIdleSwiID;
    g_uwIdleSwiID = COMPOSE_PID(SRE_GetCoreID(), 0);
    uwRet = __SRE_SwiDelete(g_uwIdleSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_DELETE_IDLE_SWI, uwRet);
    g_uwIdleSwiID = uwSwiID;
    return SRE_OK;
}

/**
*-@test  UT_SwiDelete_004
*-@tspec 删除软中断
*-@ttitle软中断未创建。
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDelete_004()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_ATTRIBUTE_S *pstSwiAttr;
    UINT16 usStatus;

    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum - 1);
    pstSwiAttr = &g_stSwiData.pstList[g_usSwiMaxNum - 1];
    usStatus = pstSwiAttr->usStatus;
    pstSwiAttr->usStatus = OS_SWI_UNUSED;
    uwRet = __SRE_SwiDelete(uwSwiID);
    pstSwiAttr->usStatus = usStatus;
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_NOT_CREATED, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SwiDelete_005
*-@tspec 删除软中断
*-@ttitle软中断待处理的消息数非0
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDelete_005()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_ATTRIBUTE_S *pstSwiAttr;
    UINT32 uwNumOfMsg;
    UINT16 usStatus;

    /*backup SCB*/
    pstSwiAttr = &g_stSwiData.pstList[g_usSwiMaxNum - 1];
    uwNumOfMsg = pstSwiAttr->uwNumOfMsg;
    usStatus = pstSwiAttr->usStatus;

    /*test*/
    pstSwiAttr->uwNumOfMsg = 1;
    pstSwiAttr->usStatus = OS_SWI_CREATED;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum - 1);
    uwRet = __SRE_SwiDelete(uwSwiID);

    /*restore SCB*/
    pstSwiAttr->usStatus = usStatus;
    pstSwiAttr->uwNumOfMsg = uwNumOfMsg;

    /*assert*/
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_MSG_NONZERO, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SwiDelete_006
*-@tspec 删除软中断
*-@ttitle软中断处于ACTIVE状态
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDelete_006()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_ATTRIBUTE_S *pstSwiAttr;
    UINT16 usStatus;

    /*backup SCB*/
    pstSwiAttr = &g_stSwiData.pstList[g_usSwiMaxNum - 1];
    usStatus = pstSwiAttr->usStatus;

    /*test*/
    pstSwiAttr->usStatus = (OS_SWI_CREATED | OS_SWI_ACTIVE);
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum - 1);
    uwRet = __SRE_SwiDelete(uwSwiID);

    /*restore SCB*/
    pstSwiAttr->usStatus = usStatus;

    /*assert*/
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ACTIVE_DEL_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SwiDelete_007
*-@tspec 删除软中断
*-@ttitle软中断删除成功
*/
OS_SEC_TEXT_UT UINT32 UT_SwiDelete_007()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID = 0xff;
    UINT16 usPrioLvl = 0xff;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "swi_del_008";
    stInitPara.usPriority = OS_SWI_PRIORITY_LOWEST;
    stInitPara.pfnHandler = (SWI_PROC_FUNC)0x111111;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usPrioLvl = __SRE_SwiDisable();
    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
EXIT:
    if (0xff != usPrioLvl) __SRE_SwiEnable(usPrioLvl);
    if (0xff != uwSwiID) (void)__SRE_SwiDelete(uwSwiID);
    return SRE_OK;
}

OS_SEC_TEXT_UT VOID UT_sre_swi_init()
{
    UINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_sre_swi_init");

    TEST_ADD_CASE(UT_osSwiRegister_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_osSwiInit_001, uiSuiteId, Label_RUN);
   // TEST_ADD_CASE(UT_osSwiInit_002, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_osSwiActivate_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_010, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiCreate_011, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDelete_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDelete_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDelete_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDelete_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDelete_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDelete_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SwiDelete_007, uiSuiteId, Label_RUN);

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             