 /**
 * @file:ut_sre_msg_init.c
 *
 * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * Author: c00180607
 */
#include "iCunit.h"
#include "sre_base.h"
#include "sre_sys.h"
#include "sre_typedef.h"
#include "sre_task.h"
#include "sre_hunt.h"
#include "sre_hwi.h"
#include "sre_swi.h"
//#include "sre_sync.h"
#include "iCunit.h"
#include "osTest.h"
#include "sre_config.h"
#include "app_data_common.h"
#include "osTest.h"
#include "sre_msg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
extern UINT32 osMsgRegister(MSG_MOD_INFO_S *pstModInfo);
extern UINT32 osMsgInit(VOID);

extern UINT32 g_uwMaxMsgNum;           /* 用户配置的最大核内消息节点数 */
/**
*-@test  ut_osMsgRegister_001
*-@tspec  配置注册消息结点接口测试
*-@ttitle  配置消息结点个数
*-@tprecon
*-@tbrief
1.配置消息结点 个数为零
*-@texpect
1.注册消息结点失败
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/

OS_SEC_TEXT3_UT UINT32 ut_osMsgRegister_001()
{
    UINT32 uwRet;
    MSG_MOD_INFO_S stModInfo;
    stModInfo.uwMaxMsgNum = 0;
    uwRet = osMsgRegister(&stModInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_REG_ERROR, uwRet);
    return SRE_OK;
}

/**
*-@test  ut_osMsgInit_001
*-@tspec  配置注册消息结点接口测试
*-@ttitle  配置消息结点个数
*-@tprecon
*-@tbrief
1.配置消息结点 个数为0x100000000
*-@texpect
1.消息结点初始化失败
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/

OS_SEC_TEXT3_UT UINT32 ut_osMsgInit_001()
{
    UINT32 uwRet;
    MSG_MOD_INFO_S stModInfo;
    stModInfo.uwMaxMsgNum = g_uwMaxMsgNum;

    g_uwMaxMsgNum = 0x1000000;
    uwRet = osMsgInit();
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_NO_MEMORY, uwRet);

    g_uwMaxMsgNum = stModInfo.uwMaxMsgNum;

    return SRE_OK;
}

/**
*-@test  ut_osMsgInit_002
*-@tspec  配置注册消息结点接口测试
*-@ttitle  配置消息结点个数
*-@tprecon
*-@tbrief
1.配置消息结点 个数为2
*-@texpect
1.消息结点初始化
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/

OS_SEC_TEXT3_UT UINT32 ut_osMsgInit_002()
{
    UINT32 uwRet;
    MSG_MOD_INFO_S stModInfo;
    stModInfo.uwMaxMsgNum = g_uwMaxMsgNum;

    g_uwMaxMsgNum = 16;
    uwRet = osMsgInit();
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    g_uwMaxMsgNum = stModInfo.uwMaxMsgNum;

    return SRE_OK;
}


/* 入口测试套  */
OS_SEC_TEXT3_UT void UT_sre_msg_init(void)
{
    iUINT32 uiSuiteId;
    TEST_ADD_SUITE(uiSuiteId, "UT_sre_msg_init");
    TEST_ADD_CASE(ut_osMsgRegister_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_osMsgInit_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(ut_osMsgInit_002, uiSuiteId, Label_RUN);初始化测试，重新申请静态内存，重新初始化消息结点，会改变后面的用例逻辑
Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
