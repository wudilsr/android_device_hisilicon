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

extern UINT32 g_uwMaxMsgNum;           /* �û����õ���������Ϣ�ڵ��� */
/**
*-@test  ut_osMsgRegister_001
*-@tspec  ����ע����Ϣ���ӿڲ���
*-@ttitle  ������Ϣ������
*-@tprecon
*-@tbrief
1.������Ϣ��� ����Ϊ��
*-@texpect
1.ע����Ϣ���ʧ��
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
*-@tspec  ����ע����Ϣ���ӿڲ���
*-@ttitle  ������Ϣ������
*-@tprecon
*-@tbrief
1.������Ϣ��� ����Ϊ0x100000000
*-@texpect
1.��Ϣ����ʼ��ʧ��
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
*-@tspec  ����ע����Ϣ���ӿڲ���
*-@ttitle  ������Ϣ������
*-@tprecon
*-@tbrief
1.������Ϣ��� ����Ϊ2
*-@texpect
1.��Ϣ����ʼ��
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


/* ��ڲ�����  */
OS_SEC_TEXT3_UT void UT_sre_msg_init(void)
{
    iUINT32 uiSuiteId;
    TEST_ADD_SUITE(uiSuiteId, "UT_sre_msg_init");
    TEST_ADD_CASE(ut_osMsgRegister_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_osMsgInit_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(ut_osMsgInit_002, uiSuiteId, Label_RUN);��ʼ�����ԣ��������뾲̬�ڴ棬���³�ʼ����Ϣ��㣬��ı����������߼�
Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
