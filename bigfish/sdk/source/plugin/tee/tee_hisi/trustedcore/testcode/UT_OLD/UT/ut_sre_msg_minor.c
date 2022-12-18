 /**
 * @file:ut_src_msg_minor.c
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
#include "sre_msg.ph"
#include "sre_mem.h"
#include "Set_Peg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define TST_TSK_PRIOR_HIGH1            OS_TSK_PRIORITY_24
#define TST_TSK_PRIOR_LOW1             OS_TSK_PRIORITY_26

extern UINT32 g_uwMaxMsgNum;           /* �û����õ���������Ϣ�ڵ��� */

TSK_HANDLE_T uwTestTskHdl;
//����������Ҫ�õĵı���
extern  TSK_HANDLE_T       g_uwIdleTaskID;
extern UINT32 auwITestMcTskID[OS_SYNC_CORE_NUM];
extern volatile UINT32 m_uwMcMsgCount[OS_SYNC_CORE_NUM];
extern UINT32 osMsgmInit();

OS_SEC_TEXT3_UT VOID TST_MsgTskEntry()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    MSG_HANDLE_T uwHandle;
    uwHandle = __SRE_MsgReceive( OS_WAIT_FOREVER, NULL, NULL);

    (VOID)__SRE_TaskResume(uwTestTskHdl);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

/**
*-@test  ut___SRE_MsgAlloc_001
*-@tspec  ������Ϣ���ڴ�ӿڲ���
*-@ttitle  �������������Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.����ķ����Ų������ڵ������õ����֧�ַ�����
*-@texpect
1.����ʧ�ܣ���¼�����룬������0
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgAlloc_001()
{
    UINT32 uwHandle;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_MAX_PT_NUM + 3,10,0);
    ICUNIT_ASSERT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);
    return SRE_OK;
}


/**
*-@test  ut___SRE_MsgAlloc_002
*-@tspec  ������Ϣ���ڴ�ӿڲ���
*-@ttitle  �������������Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�������Ϣ���ڴ��С����Ϊ�㣬
*-@texpect
1.����ʧ�ܣ���¼�����룬������0ֵ
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgAlloc_002()
{
    UINT32 uwHandle;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,0,0);
    ICUNIT_ASSERT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);
    return SRE_OK;
}

/**
*-@test  ut___SRE_MsgAlloc_003
*-@tspec  ������Ϣ���ڴ�ӿڲ���
*-@ttitle  �������������Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�������Ϣ���ڴ��С������0x10000000,Զ����������ʱ���ڴ棬
*-@texpect
1.����ʧ�ܣ���¼�����룬������0ֵ
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgAlloc_003()
{
    UINT32 uwHandle;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,0x10000000,0);
    ICUNIT_ASSERT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);
    return SRE_OK;
}

/**
*-@test  ut___SRE_MsgAlloc_004
*-@tspec  ������Ϣ���ڴ�ӿڲ���
*-@ttitle  �������������Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�������Ϣ���ڴ��ַ����ֵ����8
*-@texpect
1.����ʧ�ܣ���¼�����룬������0ֵ
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgAlloc_004()
{
    UINT32 uwHandle;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,10,9);
    ICUNIT_ASSERT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);
    return SRE_OK;
}
#if 0
/**
*-@test  ut_SRE_MsgAlloc_005
*-@tspec  ������Ϣ���ڴ�ӿڲ���
*-@ttitle  �������������Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.��Ϣ���ڴ��С������8�ֽڣ��ظ�����ֱ����������Ϣ����ù�
*-@texpect
1.����ʧ�ܣ�����0ֵ
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgAlloc_005()
{
    UINT32 uwHandle[32] = {0};
    UINT32 uwLoop;
    UINT32 uwRet;

    for(uwLoop = 0; uwLoop < g_uwMaxMsgNum; uwLoop++)
    {
        uwHandle[uwLoop] = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,8,5);
        ICUNIT_ASSERT_NOT_EQUAL(uwHandle[uwLoop], OS_MSG_CREATE_ERR, uwHandle[uwLoop]);
    }

    uwHandle[uwLoop] = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,8,5);
    ICUNIT_ASSERT_EQUAL(uwHandle[uwLoop], OS_MSG_CREATE_ERR, uwHandle[uwLoop]);

    for(uwLoop = 0; uwLoop < g_uwMaxMsgNum; uwLoop++)
    {
        uwRet = SRE_MsgFree(uwHandle[uwLoop]);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }
    return SRE_OK;
}
#endif
/**
*-@test  ut___SRE_MsgAlloc_006
*-@tspec  ������Ϣ���ڴ�ӿڲ���
*-@ttitle  ��ȷ���������Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�������ķ����ţ����ʵ��ڴ��С�����������[0,8]��Χ��
*-@texpect
1.��Ϣ���ڴ�����ɹ���������Ϣ���ڴ���
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgAlloc_006()
{
    UINT32 uwHandle;
    UINT32 uwRet;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,10,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    memset((UINT8*)uwHandle,1,10);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test  ut___SRE_MsgAlloc_007
*-@tspec  ������Ϣ���ڴ�ӿڲ���
*-@ttitle  ��ȷ���������Ϣ���ڴ棬��ַ�������
*-@tprecon
*-@tbrief
1.�������ķ����ţ���Ϣ������ַ����Ϊ128�ֽڣ�������ݣ��õ�ַ����128
*-@texpect
1.��Ϣ���ڴ�����ɹ�����ַ����128�ֽڳɹ�
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgAlloc_007()
{
    UINT32 uwHandle;
    UINT32 uwRet;
    UINT16 usSize;

    usSize = 10;
    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,7);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);
    ICUNIT_ASSERT_EQUAL(uwHandle%128, 0, uwHandle%128);

    strncpy((VOID *)uwHandle, "Hello!", usSize);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test  ut___SRE_MsgAlloc_008
*-@tspec  ������Ϣ���ڴ�ӿڲ���
*-@ttitle  �������������Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�������ķ����ţ�����SIZE����Ϊ0xFFFFFFFF
*-@texpect
1.�����ڴ�ʧ��
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgAlloc_008()
{
    UINT32 uwHandle;
    UINT32 uwRet;
    UINT16 usSize;

    usSize = 0xFFFFFFFF;
    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,7);
    ICUNIT_ASSERT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    return SRE_OK;
}

/**
*-@test  ut_SRE_MsgDelete_001
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle  ��������ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�������Ϣ����Ϊ�գ�
*-@texpect
1.�򷵻ش�����OS_ERRNO_MSG_HANDLE_INVALID
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_001()
{
    UINT32 uwRet;
    uwRet = SRE_MsgFree(0);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_HANDLE_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  ut_SRE_MsgDelete_002
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle  ��������ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�������Ϣ������32�ֽڶ���
*-@texpect
1.�򷵻ش�����OS_ERRNO_MSG_HANDLE_ADDR_UNALIGN
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_002()
{
    UINT32 uwHandle;
    UINT32 uwRet;
    UINT32 uwHandle2;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,10,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);
    memset((UINT8*)uwHandle,1,10);

    uwHandle2 = uwHandle - 4;
    uwRet = SRE_MsgFree(uwHandle2);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_HANDLE_ADDR_UNALIGN, uwRet,EXIT);

EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  ut_SRE_MsgDelete_003
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle  ��������ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�������Ϣ����ֵ��Ϊ�գ���32�ֽڶ��룬������������Ϣ���ڴ淵�صľ��ֵ
*-@texpect
1.�򷵻ش�����OS_ERRNO_MSG_HANDLE_INVALID
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_003()
{
    UINT32 *puwHandle;
    UINT32 uwRet;

    puwHandle = SRE_MemAllocAlign(OS_MID_MSG, OS_MEM_DEFAULT_LCDYN_PT, 10, MEM_ADDR_ALIGN_032);

    uwRet = SRE_MsgFree(*puwHandle);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_HANDLE_INVALID, uwRet, EXIT);

EXIT:
    uwRet = SRE_MemFree(OS_MID_MSG, puwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}
/**
*-@test  ut_SRE_MsgDelete_004
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle  ��������ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�ظ��ͷų���Ϣ���ڴ�
*-@texpect
1.�򷵻ش�����OS_ERRNO_MSG_HANDLE_INVALID
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_004()
{
    UINT32 uwHandle;
    UINT32 uwRet;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,10,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    memset((UINT8*)uwHandle,1,10);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_LMSG_CAN_NOT_DELETE, uwRet);

    return SRE_OK;
}
#if 0
/**
*-@test  ut_SRE_MsgDelete_005
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle  ��������ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.�ظ��ͷų���Ϣ���ڴ�
*-@texpect
1.�򷵻ش�����OS_ERRNO_MSG_HANDLE_INVALID
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_005()
{
    UINT32 uwHandle;
    UINT32 uwRet;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,8,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_SMSG_CAN_NOT_DELETE, uwRet);

    return SRE_OK;
}
#endif
/**
*-@test  ut_SRE_MsgDelete_006
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle  ����Ϣ���ڴ�δ�����մ���ֱ��ɾ��
*-@tprecon
*-@tbrief
1.����һ�������ȼ�����
2.��ȡ������PID
3.�ڲ��������з���һ������Ϣ�������ȼ�����
4.ɾ������Ϣ��
5.�������������
6.���ȼ�������յ����������͵���Ϣ��
7.�ڲ���������ɾ������Ϣ
*-@texpect
1.����һ�������ȼ�����ɹ�
2.��ȡ������PID�ɹ�
3.�ڲ��������з���һ������Ϣ�����Ϣ�������ȼ�����ɹ�
4.ɾ������Ϣ��ʧ�ܣ����ش�����OS_ERRNO_MSG_LMSG_IN_USE
5.�������������ɹ�
6.���ȼ�������յ����������͵���Ϣ��ɹ�
7.�ڲ���������ɾ������Ϣ�ɹ�
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_006()
{
    UINT32 uwHandle;
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 1;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,10,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle, EXIT);

    memset((UINT8*)uwHandle,1,10);

    uwRet = __SRE_MsgQSend(uwHandle, 2, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_LMSG_CAN_NOT_DELETE, uwRet,EXIT);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskSuspend(uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}
#if 0
/**
*-@test  ut_SRE_MsgDelete_007
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle  ����Ϣ���ڴ�δ�����մ���ֱ��ɾ��
*-@tprecon
*-@tbrief
1.����һ�������ȼ�����
2.��ȡ������PID
3.�ڲ��������з���һ������Ϣ�������ȼ�����
4.ɾ������Ϣ��
5.�������������
6.���ȼ�������յ����������͵Ķ���Ϣ
7.�ڲ���������ɾ������Ϣ
*-@texpect
1.����һ�������ȼ�����ɹ�
2.��ȡ������PID�ɹ�
3.�ڲ��������з���һ������Ϣ�������ȼ�����ɹ�
4.ɾ������Ϣ��ʧ�ܣ����ش�����OS_ERRNO_MSG_SMSG_IN_USE
5.�������������ɹ�
6.���ȼ�������յ����������͵Ķ���Ϣ�ɹ�
7.�ڲ���������ɾ������Ϣ�ɹ�
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_007()
{
    UINT32 uwHandle;
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 1;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,8,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle, EXIT);

    uwRet = __SRE_MsgSend(uwHandle, 2, uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_SMSG_CAN_NOT_DELETE, uwRet, EXIT);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskSuspend(uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}
#endif
/**
*-@test  ut_SRE_MsgDelete_008
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle ��ȷ����ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.ȷ�ϸ���Ϣ�Ѿ����մ�����Ϻ��������Ϣ����ֵΪ��Ӧ�������Ϣ���ڴ淵��ֵ
*-@texpect
1.��Ϣ���ڴ��ͷųɹ�
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_008()
{
    UINT32 uwHandle;
    UINT32 uwRet;

    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_MCDYN_PT,10,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    memset((UINT8*)uwHandle,1,10);

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test  ut_SRE_MsgDelete_009
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle ��������ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.������ֵΪ1
*-@texpect
1.ɾ��ʧ�ܣ����ش�����
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_009()
{
    UINT32 uwRet;

    uwRet = SRE_MsgFree(1);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_HANDLE_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  ut_SRE_MsgDelete_010
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle ��������ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.������ֵΪ0x4
*-@texpect
1.ɾ��ʧ�ܣ����ش�����
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_010()
{
    UINT32 uwRet;

    uwRet = SRE_MsgFree(0x4);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_HANDLE_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  ut_SRE_MsgDelete_011
*-@tspec  �ͷ���Ϣ���ڴ�ӿڲ���
*-@ttitle ��������ͷ���Ϣ���ڴ�
*-@tprecon
*-@tbrief
1.������ֵΪ0x50
*-@texpect
1.ɾ��ʧ�ܣ����ش�����
*-@tprior  1
*-@tauto TRUE
*-@tremark  ALL
*/
OS_SEC_TEXT5_UT UINT32 ut_SRE_MsgDelete_011()
{
    UINT32 uwRet;

    uwRet = SRE_MsgFree(0x50);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_HANDLE_INVALID, uwRet);
    return SRE_OK;
}


OS_SEC_TEXT5_UT UINT32 osMsgmInitSTUB()
{
    return 1;
}

  #if 0
/*
 * ����mccomģ��Ĳ�������
 * ���ӳ�ʼ����׮����
 */
OS_SEC_TEXT5_UT UINT32 ut_SRE_MCCOM_ADD_001()
{
#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
    UINT32 uwRet;
    SETPEG_JMP_ST osMcComEnQStub;
    if((OS_SYS_CORE_START + 1) == SRE_GetCoreID())
    {
        uwRet = SET_PEG(osMsgmInit, osMsgmInitSTUB, (SETPEG_JMP_ST *)&osMcComEnQStub);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        uwRet = osMcComInit();
        ICUNIT_ASSERT_EQUAL(uwRet, 1, uwRet);
        uwRet = CLEAN_PEG(osMsgmInit, osMcComEnQStub);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        uwRet = osMcComInit();
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_HWI_ALREADY_CREATED, uwRet);
    }
#endif
    return SRE_OK;
}

 #endif
/*
 * ����msgģ��Ĳ�������
 * ���ͺ˼����Ϣ    �����ý����������
 */

OS_SEC_TEXT5_UT VOID ut_SRE_MSG_ADD_001_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    MSG_HANDLE_T uwMsgHandle;
    UINT32 uwMsgID;
    UINT32 uwSenderPID;
    TSK_HANDLE_T uwTaskID;
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    __SRE_TaskSelf(&uwTaskID);
    uwMsgHandle = __SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwMsgID, 1234, uwMsgID);
    __SRE_TaskSuspend(uwTaskID);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return;
}

OS_SEC_TEXT5_UT UINT32 ut_SRE_MSG_ADD_001()
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stInitParam = {ut_SRE_MSG_ADD_001_TSK, 10, 2, {0}, 0x400, "TSK", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    UINT32 uwMsgID;
    MSG_HANDLE_T uwHandle;
    m_uwMcMsgCount[SRE_GetCoreID()] = 0;
    //SRE_WaitForAllCores();
    if((OS_SYS_CORE_START + 1) == SRE_GetCoreID())
    {
        uwRet = __SRE_TaskCreate(&auwITestMcTskID[OS_SYS_CORE_START], &stInitParam);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    }
    //SRE_WaitForAllCores();
    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwMsgID = 1234;
        uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_MCDYN_PT,6,5);
        ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT);
        memset((VOID *)uwHandle, 10, 6);
        uwRet = SRE_MsgLength(NULL);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_MSG_LENGTH_ERR, uwRet);
        uwRet = SRE_MsgLength(uwHandle+3);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_MSG_LENGTH_ERR, uwRet);

        uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, auwITestMcTskID[OS_SYS_CORE_START], 0);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }

    //SRE_WaitForAllCores();

    if((OS_SYS_CORE_START + 1) == SRE_GetCoreID())
    {
        uwRet = __SRE_TaskDelete(auwITestMcTskID[OS_SYS_CORE_START]);
        ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    }
EXIT:
    //SRE_WaitForAllCores();
    return SRE_OK;
}
OS_SEC_TEXT5_UT UINT32 ut_SRE_MSG_ADD_002()
{
    UINT32 uwRet;
    MSG_HANDLE_T uwHandle;
    UINT32 uwMsgID;
    TSK_HANDLE_T uwTaskID;
    __SRE_TaskSelf(&uwTaskID);
    uwMsgID = 1234;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_MCDYN_PT,6,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT);
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID , g_uwIdleTaskID, 0);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_PID_INVALID, uwRet);
    uwRet = SRE_MsgQNumGet(g_uwIdleTaskID,0);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_MSGQ_NUM_GET_ERR, uwRet);
    uwRet = SRE_MsgQNumGet(uwTaskID,0);

EXIT:
    return SRE_OK;
}

 //HWI
OS_SEC_TEXT5_UT UINT32 ut_SRE_MSG_ADD_003_hwi(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
        MSG_HANDLE_T uwMsgHandle;
        UINT32 uwMsgID;
        UINT32 uwSenderPID;
        uwMsgHandle = __SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
        ICUNIT_ASSERT_EQUAL(uwMsgHandle, OS_MSG_RECEIVE_ERR, uwMsgHandle);
        return SRE_OK;
 }
 OS_SEC_TEXT5_UT UINT32 ut_SRE_MSG_ADD_003()
 {
     UINT32 uwRet;
     HWI_HANDLE_T uwHwiNum = 7;
     HWI_PRIOR_T usHwiPrio = 0xa0;
     HWI_MODE_T uwHwiMode =  0x4000;
     //SRE_WaitForAllCores();
     //uwRet = SRE_HwiSetAttr(uwHwiNum, usHwiPrio, uwHwiMode);
     uwRet = __SRE_HwiCreate(uwHwiNum,usHwiPrio,IT_HWI_SECURE_MODE, (HWI_PROC_FUNC)ut_SRE_MSG_ADD_003_hwi, uwHwiNum);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     __SRE_HwiEnable(7);
     //SRE_WaitForAllCores();
	 __SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), uwHwiNum);
     //SRE_WaitForAllCores();
     (VOID)__SRE_HwiClearPendingBit(uwHwiNum);
     uwRet = __SRE_HwiDelete(uwHwiNum);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     //SRE_WaitForAllCores();
     return SRE_OK;
 }

 OS_SEC_TEXT5_UT VOID ut_SRE_MSG_ADD_004_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     MSG_HANDLE_T uwMsgHandle;
     UINT32 uwMsgID;
     UINT32 uwSenderPID;
     TSK_HANDLE_T uwTaskID;
     UINT32 uwRet;
     __SRE_TaskSelf(&uwTaskID);
     uwRet = SRE_MsgQRecv(&uwMsgHandle, &uwMsgID, &uwSenderPID, 0, 0);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_MSG_QUEUE_EMPTY, uwRet);
     uwRet = SRE_MsgQRecv(&uwMsgHandle, &uwMsgID, &uwSenderPID, 3, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet);
     uwRet = SRE_MsgQRecv(&uwMsgHandle, &uwMsgID, &uwSenderPID, 0, 1000);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
     __SRE_TaskSuspend(uwTaskID);
     return;
 }
 OS_SEC_TEXT5_UT UINT32 ut_SRE_MSG_ADD_004()
 {
        UINT32 uwRet;
        TSK_INIT_PARAM_S stInitParam = {ut_SRE_MSG_ADD_004_TSK, 10, 2, {0}, 0x600, "TSK4", 0, 0, OS_MEM_DEFAULT_FSC_PT};
        UINT32 uwMsgID;
        MSG_HANDLE_T uwHandle;
        m_uwMcMsgCount[SRE_GetCoreID()] = 0;
        //SRE_WaitForAllCores();
        if((OS_SYS_CORE_START + 1) == SRE_GetCoreID())
        {
            uwRet = __SRE_TaskCreate(&auwITestMcTskID[OS_SYS_CORE_START], &stInitParam);
            ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
        }
        //SRE_WaitForAllCores();
        if(OS_SYS_CORE_START == SRE_GetCoreID())
        {
            uwMsgID = 1234;
            uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_MCDYN_PT,6,5);
            ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT);
            memset((VOID *)uwHandle, 10, 6);
            uwRet = SRE_MsgQSend(uwHandle, uwMsgID, auwITestMcTskID[OS_SYS_CORE_START],10);
            ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet);
            uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, auwITestMcTskID[OS_SYS_CORE_START], 0);
            ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        }
        //SRE_WaitForAllCores();
        if((OS_SYS_CORE_START + 1) == SRE_GetCoreID())
        {
            uwRet = __SRE_TaskDelete(auwITestMcTskID[OS_SYS_CORE_START]);
            ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
        }
    EXIT:
        //SRE_WaitForAllCores();
        return SRE_OK;
 }
/* ��ڲ�����  */
OS_SEC_TEXT3_UT void UT_sre_msg_minor(void)
{
    iUINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_sre_msg_minor");
    TEST_ADD_CASE(ut_SRE_MsgAlloc_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_SRE_MsgAlloc_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_SRE_MsgAlloc_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_SRE_MsgAlloc_004, uiSuiteId, Label_RUN);
//#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
    //TEST_ADD_CASE(ut_SRE_MsgAlloc_005, uiSuiteId, Label_RUN);
//#endif
    TEST_ADD_CASE(ut_SRE_MsgAlloc_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_SRE_MsgAlloc_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_SRE_MsgAlloc_008, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(ut_SRE_MsgDelete_001, uiSuiteId, Label_RUN);
//#if ((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170))
    TEST_ADD_CASE(ut_SRE_MsgDelete_002, uiSuiteId, Label_RUN);
//#endif
   // TEST_ADD_CASE(ut_SRE_MsgDelete_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_SRE_MsgDelete_004, uiSuiteId, Label_RUN);
//#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
   // TEST_ADD_CASE(ut_SRE_MsgDelete_005, uiSuiteId, Label_RUN);
//#endif
    TEST_ADD_CASE(ut_SRE_MsgDelete_006, uiSuiteId, Label_RUN);
//#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
   // TEST_ADD_CASE(ut_SRE_MsgDelete_007, uiSuiteId, Label_RUN);
//#endif
    //TEST_ADD_CASE(ut_SRE_MsgDelete_008, uiSuiteId, Label_RUN);

   //////��������
//#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
    //TEST_ADD_CASE(ut_SRE_MCCOM_ADD_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(ut_SRE_MSG_ADD_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(ut_SRE_MSG_ADD_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(ut_SRE_MSG_ADD_003, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(ut_SRE_MSG_ADD_004, uiSuiteId, Label_RUN);
//#endif

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            








                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            