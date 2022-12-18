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
//#include <string.h>
#include "osTest.h"
#include "app_data_common.h"

extern UINT32 osSwiInit(VOID);
extern UINT32 osSwiRegister(SWI_MOD_INFO_S *pstModInfo);

extern UINT16 g_usSwiMaxNum;
extern SWI_ATTRIBUTE_S *g_pstSwiActive;

UINT32 g_uwSwiTrigTime2;
UINT32 g_uwSwiPID = 0xff;
UINT8 g_ucMcSwiTrigType = 0xff;

OS_SEC_TEXT_UT VOID UT_Swi_Func_minor_001(UINT32 uwArg)
{
    g_uwSwiTrigTime2++;
}

OS_SEC_TEXT UINT32 UT_McSwiActive(UINT32 uwDstPid, UINT8 ucOprtType, UINT32 uwOprtNum)
{
    g_ucMcSwiTrigType = ucOprtType;
    return SRE_OK;
}


/**
*-@test  UT_SRE_SwiSelf_001
*-@tspec 查询当前软中断信息
*-@ttitle指针参数为空。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiSelf_001()
{
    UINT32 uwRet;
    uwRet = __SRE_SwiSelf(NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_SELF_PTR_NULL, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiSelf_002
*-@tspec 查询当前软中断信息
*-@ttitle软中断未激活。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiSelf_002()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    volatile SWI_ATTRIBUTE_S *pstSwiActive;
    UINTPTR uvIntSave;

    uvIntSave = __SRE_IntLock();
    pstSwiActive = g_pstSwiActive;
    g_pstSwiActive = NULL;
    uwRet = __SRE_SwiSelf(&uwSwiID);
    g_pstSwiActive = (SWI_ATTRIBUTE_S *)pstSwiActive;
    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_NOT_ACTIVE, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiSelf_003
*-@tspec 查询当前软中断信息
*-@ttitle软中断未激活。
*/
OS_SEC_TEXT_UT VOID UT_SRE_SwiSelf_003_f01(UINT32 uwArg)
{
    UINT32 uwRet;
    UINT32 uwSwiID;

    uwRet = __SRE_SwiSelf(&uwSwiID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    ICUNIT_ASSERT_EQUAL_VOID(uwSwiID, g_uwSwiPID, uwSwiID);
}


OS_SEC_TEXT_UT UINT32 UT_SRE_SwiSelf_003()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_self_03";
    stInitPara.usPriority = 10;
    stInitPara.pfnHandler = UT_SRE_SwiSelf_003_f01;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&g_uwSwiPID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiActivate(g_uwSwiPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiDelete(g_uwSwiPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiSelf_004
*-@tspec 查询当前软中断信息
*-@ttitle软中断未激活。
*/
OS_SEC_TEXT_UT VOID UT_SRE_SwiSelf_004_f02(UINT32 uwArg)
{
    UINT32 uwRet;
    UINT32 uwSwiID;

    uwRet = __SRE_SwiSelf(&uwSwiID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    ICUNIT_ASSERT_EQUAL_VOID(uwSwiID, g_uwSwiPID, uwSwiID);
}

OS_SEC_TEXT_UT VOID UT_SRE_SwiSelf_004_f01(UINT32 uwArg)
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_self_04";
    stInitPara.usPriority = 1;
    stInitPara.pfnHandler = UT_SRE_SwiSelf_004_f02;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&g_uwSwiPID, &stInitPara);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiActivate(g_uwSwiPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiDelete(g_uwSwiPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
}

OS_SEC_TEXT_UT UINT32 UT_SRE_SwiSelf_004()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swi_self_03";
    stInitPara.usPriority = 10;
    stInitPara.pfnHandler = UT_SRE_SwiSelf_004_f01;
    stInitPara.uwInitValue = 0;

    /*创建软中断*/
    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test
*-@tspec 查询软中断状态
*-@ttitle软中断ID非法
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiStatusGet_001()
{
    SWI_HANDLE_T uwSwiID;
    SWI_STATUS_T usStatus;

    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), 0xef);
    usStatus = __SRE_SwiStatusGet(uwSwiID);
    ICUNIT_ASSERT_EQUAL(usStatus, 0xFFFF, usStatus);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiStatusGet_002
*-@tspec 查询软中断状态
*-@ttitle查询其他核的软中断状态
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiStatusGet_002()
{
    SWI_HANDLE_T uwSwiID;
    SWI_STATUS_T usStatus;

    uwSwiID = COMPOSE_PID(SRE_GetCoreID()+1, 0);
    usStatus = __SRE_SwiStatusGet(uwSwiID);
    ICUNIT_ASSERT_EQUAL(usStatus, 0xFFFF, usStatus);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiStatusGet_003
*-@tspec 查询软中断号
*-@ttitle软中断未创建。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiStatusGet_003()
{
    SWI_HANDLE_T uwSwiID;
    SWI_STATUS_T usStatus;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum-1);
    usStatus = __SRE_SwiStatusGet(uwSwiID);
    ICUNIT_ASSERT_EQUAL(usStatus, OS_SWI_UNUSED, usStatus);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiStatusGet_004
*-@tspec 查询已创建的软中断状态
*-@ttitle软中断未创建。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiStatusGet_004()
{

    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    UINT16 usStatus;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swiStat_005";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_Swi_Func_minor_001;
    stInitPara.uwInitValue = 12;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usStatus = __SRE_SwiStatusGet(uwSwiID);
    ICUNIT_ASSERT_EQUAL(usStatus, OS_SWI_CREATED, usStatus);

    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiStatusGet_005
*-@tspec 查询已创建的软中断状态
*-@ttitle软中断未创建。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiStatusGet_005_f01()
{
    UINT16 usStatus;
    SWI_HANDLE_T uwSwiID;
    UINT32 uwRet;

    uwRet = __SRE_SwiSelf(&uwSwiID);
    usStatus = __SRE_SwiStatusGet(uwSwiID);
    ICUNIT_ASSERT_EQUAL(usStatus, OS_SWI_ACTIVE | OS_SWI_CREATED, usStatus);

}

OS_SEC_TEXT_UT UINT32 UT_SRE_SwiStatusGet_005()
{

    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swiStat_005";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_SRE_SwiStatusGet_005_f01;
    stInitPara.uwInitValue = 12;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiValueGet_001
*-@tspec 查询软中断触发时的锁定值
*-@ttitle软中断未激活。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiValueGet_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    volatile SWI_ATTRIBUTE_S *pstSwiActive;
    UINTPTR uvIntSave;

    uvIntSave = __SRE_IntLock();
    pstSwiActive = g_pstSwiActive;
    g_pstSwiActive = NULL;
    uwRet = __SRE_SwiValueGet();
    g_pstSwiActive = (SWI_ATTRIBUTE_S *)pstSwiActive;
    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(uwRet, (UINT32)-1, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiValueGet_002
*-@tspec __SRE_SwiInc
*-@ttitle软中断ID非法。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiValueGet_002()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), 0xef);
    uwRet = __SRE_SwiInc(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_ACT_INC_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiValueGet_003
*-@tspec 查询软中断触发时的锁定值
*-@ttitle软中断未激活。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiValueGet_003()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    volatile SWI_ATTRIBUTE_S *pstSwiActive;
    UINTPTR uvIntSave;

    uvIntSave = __SRE_IntLock();
    pstSwiActive = g_pstSwiActive;
    g_pstSwiActive = NULL;
    uwRet = __SRE_SwiValueGet();
    g_pstSwiActive = (SWI_ATTRIBUTE_S *)pstSwiActive;
    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(uwRet, (UINT32)-1, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiValueGet_004
*-@tspec 查询软中断触发时的锁定值
*-@ttitle软中断未激活。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiValueGet_004()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    volatile SWI_ATTRIBUTE_S *pstSwiActive;
    UINTPTR uvIntSave;
    SWI_ATTRIBUTE_S stSwiActiveTemp;

    stSwiActiveTemp.uwLockValue = 10;

    uvIntSave = __SRE_IntLock();

    pstSwiActive = g_pstSwiActive;
    g_pstSwiActive = &stSwiActiveTemp;

    uwRet = __SRE_SwiValueGet();
    ICUNIT_ASSERT_EQUAL(uwRet, 10, uwRet);

    g_pstSwiActive = (SWI_ATTRIBUTE_S *)pstSwiActive;
    __SRE_IntRestore(uvIntSave);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiInc_001
*-@tspec __SRE_SwiInc
*-@ttitle软中断未创建
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInc_001()
{
    UINT32 uwRet;
    UINT32 uwSwiID;

    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum-1);
    uwRet = __SRE_SwiInc(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ACT_INC_NOT_CREATED, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiInc_002
*-@tspec __SRE_SwiInc
*-@ttitle增加软中断计数且激活。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInc_002()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swiinc_002";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_Swi_Func_minor_001;
    stInitPara.uwInitValue = 12;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    g_uwSwiTrigTime2 = 0;
    uwRet = __SRE_SwiInc(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    ICUNIT_GOTO_EQUAL(g_uwSwiTrigTime2, 1, g_uwSwiTrigTime2,EXIT);
EXIT:
    __SRE_SwiDelete(uwSwiID);
    return SRE_OK;
}
#if 0
/**
*-@test  UT_SRE_SwiInc_003
*-@tspec 增加软中断
*-@ttitle核间软中断触发失败。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInc_003()
{
    UINT32  uwRet;
    UINTPTR uvIntSave;
    UINT32  uwSwiID;
    OS_MCSWI_ACTIVE_FUNC pfnMcSwiActive;

    uwSwiID = COMPOSE_PID(SRE_GetMasterCore(), g_usSwiMaxNum - 1);

    if (SRE_GetMasterCore() != SRE_GetCoreID())
    {
        uvIntSave = __SRE_IntLock();
        pfnMcSwiActive = g_pfnMcSwiActive;
        g_pfnMcSwiActive = osMcSwiActNullHandler;
        uwRet = __SRE_SwiInc(uwSwiID);
        g_pfnMcSwiActive = pfnMcSwiActive;
        __SRE_IntRestore(uvIntSave);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_MC_INT_FAIL, uwRet);
    }

    return SRE_OK;
}
#endif
/**
*-@test  UT_SRE_SwiInc_004
*-@tspec 增加软中断
*-@ttitle核间软中断触发成功。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInc_004()
{
    UINT32 uwRet;
    UINT32 uwSwiID;

    if (SRE_GetMasterCore() != SRE_GetCoreID())
    {
        uwSwiID = COMPOSE_PID(SRE_GetMasterCore(), g_usSwiMaxNum - 2);
        uwRet = __SRE_SwiInc(uwSwiID);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }

    return SRE_OK;
}
#if 0
/**
*-@test  UT_SRE_SwiInc_005
*-@tspec 增加软中断
*-@ttitle核间中断触发失败。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInc_005()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    OS_MCSWI_ACTIVE_FUNC pfnTemp;
    UINTPTR uvIntSave;

    uwSwiID = COMPOSE_PID(SRE_GetMasterCore() + SRE_GetMaxNumberOfCores(), g_usSwiMaxNum - 2);
    if (SRE_GetMasterCore() != SRE_GetCoreID())
    {
        uwRet = __SRE_SwiInc(uwSwiID);
        ICUNIT_ASSERT_NOT_EQUAL(uwRet, SRE_OK, uwRet);
    }
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiInc_006
*-@tspec 增加软中断
*-@ttitle激活核间软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInc_006()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    OS_MCSWI_ACTIVE_FUNC pfnTemp;
    UINTPTR uvIntSave;

    uwSwiID = COMPOSE_PID(SRE_GetMasterCore(), g_usSwiMaxNum - 1);
    if (SRE_GetMasterCore() != SRE_GetCoreID())
    {
        uvIntSave = __SRE_IntLock();
        pfnTemp = g_pfnMcSwiActive;
        g_pfnMcSwiActive = UT_McSwiActive;
        uwRet = __SRE_SwiInc(uwSwiID);
        g_pfnMcSwiActive = pfnTemp;
        __SRE_IntRestore(uvIntSave);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        ICUNIT_ASSERT_EQUAL(g_ucMcSwiTrigType, MCCOM_SWI_INC, g_ucMcSwiTrigType);
    }
    return SRE_OK;
}
#endif
/**
*-@test  UT_SRE_SwiDec_001
*-@tspec 增加软中断
*-@ttitle软中断ID非法
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiDec_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), 0xef);
    uwRet = __SRE_SwiDec(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_ACT_DEC_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiDec_002
*-@tspec 增加软中断
*-@ttitle软中断未创建
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiDec_002()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), 14);
    uwRet = __SRE_SwiDec(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ACT_DEC_NOT_CREATED, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiDec_003
*-@tspec 增加软中断
*-@ttitle软中断创建成功
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiDec_003()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_PRIOR_T usPrior;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swidec_003";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_Swi_Func_minor_001;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    uwRet = __SRE_SwiDec(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    return SRE_OK;

EXIT:
    __SRE_SwiDelete(uwSwiID);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiDec_004
*-@tspec 增加软中断
*-@ttitle删除软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiDec_004()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_PRIOR_T usPrior;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swidec_004";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_Swi_Func_minor_001;
    stInitPara.uwInitValue = 2;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    uwRet = __SRE_SwiDec(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    uwRet = __SRE_SwiDec(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
EXIT:
    __SRE_SwiDelete(uwSwiID);
   return SRE_OK;

}
#if 0
/**
*-@test  UT_SRE_SwiDec_005
*-@tspec __SRE_SwiDec
*-@ttitle软中断ID核号超出范围。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiDec_005()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    uwSwiID = COMPOSE_PID(0xee, 12);
    uwRet = __SRE_SwiDec(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MCHWI_DST_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiDec_006
*-@tspec 去除软中断
*-@ttitle核间中断触发失败。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiDec_006()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    OS_MCSWI_ACTIVE_FUNC pfnTemp;
    UINTPTR uvIntSave;

    uwSwiID = COMPOSE_PID(SRE_GetMasterCore() + SRE_GetNumberOfCores(), g_usSwiMaxNum-1);

    if (SRE_GetNumberOfCores() > 1)
    {
        uvIntSave = __SRE_IntLock();

        pfnTemp = g_pfnMcSwiActive;
        g_pfnMcSwiActive = osMcSwiActNullHandler;
        uwRet = __SRE_SwiDec(uwSwiID);
        g_pfnMcSwiActive = pfnTemp;

        __SRE_IntRestore(uvIntSave);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_MC_INT_FAIL, uwRet);
    }
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiDec_007
*-@tspec 去除软中断
*-@ttitle激活核间软中断
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiDec_007()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    OS_MCSWI_ACTIVE_FUNC pfnTemp;
    UINTPTR uvIntSave;

    if (SRE_GetNumberOfCores() > 1)
    {
        uvIntSave = __SRE_IntLock();

        pfnTemp = g_pfnMcSwiActive;
        g_pfnMcSwiActive = UT_McSwiActive;
        uwSwiID = COMPOSE_PID((SRE_GetCoreID()+1)%SRE_GetNumberOfCores(), 12);
        uwRet = __SRE_SwiDec(uwSwiID);
        g_pfnMcSwiActive = pfnTemp;

        __SRE_IntRestore(uvIntSave);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        ICUNIT_ASSERT_EQUAL(g_ucMcSwiTrigType, MCCOM_SWI_DEC, g_ucMcSwiTrigType);
    }
    return SRE_OK;
}
#endif
/**
*-@test  UT_SRE_SwiOr_001
*-@tspec 增加软中断
*-@ttitle软中断ID非法
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiOr_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    UINT32 uwMask = 0;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swior_001";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_Swi_Func_minor_001;
    stInitPara.uwInitValue = 2;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    uwRet = __SRE_SwiOr(uwSwiID, uwMask);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    __SRE_SwiDelete(uwSwiID);
    return SRE_OK;
EXIT:
    __SRE_SwiDelete(uwSwiID);
    return SRE_OK;

}

/**
*-@test  UT_SRE_SwiOr_002
*-@tspec 增加软中断
*-@ttitle软中断ID的核号超出范围
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiOr_002()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    UINT32 uwMask = 0;

    uwSwiID = COMPOSE_PID(((SRE_GetCoreID() + 1) ), 12);
    uwRet = __SRE_SwiOr(uwSwiID, uwMask);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_ACT_OR_INVALID, uwRet);

    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum + 1);
    uwRet = __SRE_SwiOr(uwSwiID, uwMask);

    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_ACT_OR_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiOr_003
*-@tspec 增加软中断
*-@ttitle增量计数模式触发软中断未创建的软中断失败。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiOr_003()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    UINTPTR uvIntSave;
    UINT32 uwMask = 0;

    uvIntSave = __SRE_IntLock();

    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum - 1);
    uwRet = __SRE_SwiOr(uwSwiID, uwMask);

    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ACT_OR_NOT_CREATED, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiOr_004
*-@tspec 增加软中断
*-@ttitle增量计数模式触发软中断未创建的软中断失败。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiOr_004()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    UINTPTR uvIntSave;
    UINT32 uwMask = 0;

    uvIntSave = __SRE_IntLock();

    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum - 1);
    uwRet = __SRE_SwiOr(uwSwiID, uwMask);

    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ACT_OR_NOT_CREATED, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiAndn_001
*-@tspec 增加软中断
*-@ttitle软中断ID非法
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiAndn_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID, uwMask = 0;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), 0xef);
    uwRet = __SRE_SwiAndn(uwSwiID, uwMask);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_ACT_AND_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiAndn_002
*-@tspec 增加软中断
*-@ttitle软中断ID非法
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiAndn_002()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID, uwMask = 0;
    uwSwiID = COMPOSE_PID(SRE_GetCoreID(), 14);
    uwRet = __SRE_SwiAndn(uwSwiID, uwMask);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ACT_AND_NOT_CREATED, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiAndn_003
*-@tspec 增加软中断
*-@ttitle软中断ID非法
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiAndn_003()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    SWI_PRIOR_T usPrior;
    UINT32 uwMask = 2;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swiand_003";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_Swi_Func_minor_001;
    stInitPara.uwInitValue = uwMask;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    uwRet = __SRE_SwiAndn(uwSwiID, uwMask);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    __SRE_SwiDelete(uwSwiID);
    return SRE_OK;
EXIT:
    __SRE_SwiDelete(uwSwiID);
    return SRE_OK;

}

/**
*-@test  UT_SRE_SwiAndn_004
*-@tspec 增加软中断
*-@ttitle软中断ID非法
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiAndn_004()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    UINT32 uwMask = 2;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swiand_004";
    stInitPara.usPriority = 12;
    stInitPara.pfnHandler = UT_Swi_Func_minor_001;
    stInitPara.uwInitValue = 1;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    uwRet = __SRE_SwiAndn(uwSwiID, uwMask);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);
    __SRE_SwiDelete(uwSwiID);
    return SRE_OK;
EXIT:
    __SRE_SwiDelete(uwSwiID);
    return SRE_OK;

}

/**
*-@test  UT_SRE_SwiAndn_005
*-@tspec __SRE_SwiAndn
*-@ttitle软中断ID的索引号超出范围
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiAndn_005()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    UINT32 uwMask = 0;
    uwSwiID = COMPOSE_PID((SRE_GetCoreID()), g_usSwiMaxNum);
    uwRet = __SRE_SwiAndn(uwSwiID, uwMask);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_ACT_AND_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiAndn_006
*-@tspec __SRE_SwiAndn
*-@ttitle核间软中断触发失败
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiAndn_006()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    UINT32 uwMask = 0;

    if (SRE_GetNumberOfCores() > 1)
    {
        uwSwiID = COMPOSE_PID(((SRE_GetCoreID() + 1)%SRE_GetNumberOfCores()), 12);
        uwRet = __SRE_SwiAndn(uwSwiID, uwMask);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_ACT_AND_INVALID, uwRet);
    }
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiInfoGet_001
*-@tspec 查询软中断信息
*-@ttitle空指针。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInfoGet_001()
{
    UINT32 uwRet;

    uwRet = __SRE_SwiInfoGet(0, NULL);

    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_INFO_PTR_NULL, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiInfoGet_002
*-@tspec 查询软中断信息
*-@ttitle查询其他核的软中断信息。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInfoGet_002()
{
    UINT32 uwRet;
    UINT32 uwSwiPid;
    SWI_INFO_S stSwiInfo;

    uwSwiPid = COMPOSE_PID(SRE_GetCoreID()+1, 0);
    uwRet = __SRE_SwiInfoGet(uwSwiPid, &stSwiInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_INFO_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiInfoGet_003
*-@tspec 查询软中断信息
*-@ttitle软中断ID超出范围
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInfoGet_003()
{
    UINT32 uwRet;
    UINT32 uwSwiPid;
    SWI_INFO_S stSwiInfo;

    uwSwiPid = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum);
    uwRet = __SRE_SwiInfoGet(uwSwiPid, &stSwiInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SWI_ID_INFO_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiInfoGet_004
*-@tspec 查询软中断信息
*-@ttitle查询成功
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiInfoGet_004()
{
    UINT32 uwRet;
    UINT32 uwSwiPid;
    SWI_INFO_S stSwiInfo;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swiinfo_004";
    stInitPara.usPriority = 2;
    stInitPara.pfnHandler = (SWI_PROC_FUNC)0x12340;
    stInitPara.uwInitValue = 0;

    uwSwiPid = COMPOSE_PID(SRE_GetCoreID(), 0);
    uwRet = __SRE_SwiInfoGet(uwSwiPid, &stSwiInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiCreate(&uwSwiPid, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiInfoGet(uwSwiPid, &stSwiInfo);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(stSwiInfo.usStatus, OS_SWI_CREATED, stSwiInfo.usStatus, EXIT);
    ICUNIT_GOTO_EQUAL(stSwiInfo.usPriority, 2, stSwiInfo.usPriority, EXIT);
    ICUNIT_GOTO_EQUAL(stSwiInfo.uwNumOfMsg, 0, stSwiInfo.uwNumOfMsg, EXIT);
EXIT:
    __SRE_SwiDelete(uwSwiPid);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiPriorityGet_001
*-@tspec 查询软中断信息
*-@ttitle查询其他核的软中断信息。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiPriorityGet_001()
{
    UINT32 uwRet;
    UINT32 uwSwiPid;

    uwSwiPid = COMPOSE_PID(SRE_GetCoreID()+1, 0);
    uwRet = __SRE_SwiPriorityGet(uwSwiPid);
    ICUNIT_ASSERT_EQUAL(uwRet, (UINT16)OS_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiPriorityGet_002
*-@tspec 查询软中断信息
*-@ttitle软中断ID超出范围
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiPriorityGet_002()
{
    UINT32 uwRet;
    UINT32 uwSwiPid;

    uwSwiPid = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum);
    uwRet = __SRE_SwiPriorityGet(uwSwiPid);
    ICUNIT_ASSERT_EQUAL(uwRet, (UINT16)OS_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiPriorityGet_003
*-@tspec 查询指定软中断优先级
*-@ttitle查询成功
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiPriorityGet_003()
{
    UINT32 uwRet;
    UINT32 uwSwiPid;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_swiPri_003";
    stInitPara.usPriority = 2;
    stInitPara.pfnHandler = (SWI_PROC_FUNC)0x12340;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiPid, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiPriorityGet(uwSwiPid);
    ICUNIT_GOTO_EQUAL(uwRet, 2, uwRet, EXIT);

EXIT:
    __SRE_SwiDelete(uwSwiPid);
    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiMsgNumGet_001
*-@tspec 查询软中断信息
*-@ttitle查询其他核的软中断信息。
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiMsgNumGet_001()
{
    INT32 swRet;
    UINT32 uwSwiPid;

    uwSwiPid = COMPOSE_PID(SRE_GetCoreID()+1, 0);
    swRet = __SRE_SwiMsgNumGet(uwSwiPid);
    ICUNIT_ASSERT_EQUAL(swRet, OS_INVALID, swRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiMsgNumGet_002
*-@tspec 查询软中断信息
*-@ttitle软中断ID超出范围
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiMsgNumGet_002()
{
    INT32 swRet;
    UINT32 uwSwiPid;
    SWI_INFO_S stSwiInfo;

    uwSwiPid = COMPOSE_PID(SRE_GetCoreID(), g_usSwiMaxNum);
    swRet = __SRE_SwiMsgNumGet(uwSwiPid);
    ICUNIT_ASSERT_EQUAL(swRet, OS_INVALID, swRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_SwiMsgNumGet_003
*-@tspec 查询指定软中断优先级
*-@ttitle查询成功
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_SwiMsgNumGet_003()
{
    UINT32 uwRet;
    INT32 swRet;
    UINT32 uwSwiPid;
    SWI_INFO_S stSwiInfo;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName  = "ut_SwiMsgNum_03";
    stInitPara.usPriority = 2;
    stInitPara.pfnHandler = (SWI_PROC_FUNC)0x12340;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiPid, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    swRet = __SRE_SwiMsgNumGet(uwSwiPid);
    ICUNIT_GOTO_EQUAL(swRet, 0, swRet, EXIT);

EXIT:
    __SRE_SwiDelete(uwSwiPid);
    return SRE_OK;
}

OS_SEC_TEXT_UT VOID UT_sre_swi_minor()
{
    UINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_sre_swi_minor");
    TEST_ADD_CASE(UT_SRE_SwiSelf_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiSelf_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiSelf_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiSelf_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE( UT_SRE_SwiStatusGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiStatusGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiStatusGet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiStatusGet_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiStatusGet_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiValueGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiValueGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiValueGet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiValueGet_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiInc_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiInc_002, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_SwiInc_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiInc_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_SwiInc_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_SwiInc_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiDec_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiDec_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiDec_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiDec_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_SwiDec_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_SwiDec_006, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_SwiDec_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiOr_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiOr_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiOr_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiOr_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiAndn_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiAndn_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiAndn_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiAndn_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiAndn_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiAndn_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiInfoGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiInfoGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiInfoGet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiInfoGet_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiPriorityGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiPriorityGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiPriorityGet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiMsgNumGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiMsgNumGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_SwiMsgNumGet_003, uiSuiteId, Label_RUN);

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           