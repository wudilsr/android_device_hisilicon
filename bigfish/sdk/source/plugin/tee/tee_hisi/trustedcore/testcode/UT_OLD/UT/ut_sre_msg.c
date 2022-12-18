 /**
 * @file:
 *
 * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * @description��
 */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#include "iCunit.h"
#include "sre_base.h"
#include "sre_sys.h"
#include "sre_typedef.h"
#include "sre_task.h"
#include "sre_hunt.h"
#include "sre_hwi.h"
#include "sre_swi.h"
//#include "sre_sync.h"
#include "sre_mem.h"
#include "sre_mem.ph"
#include "iCunit.h"
#include "osTest.h"
#include "sre_config.h"
#include "app_data_common.h"
#include "osTest.h"
#include "sre_msg.h"
#include "sre_msg.ph"

//extern UINT32 osMemRegMemPtInfo(UINT8 ucPtNo, UINT32 uwSize, VOID *pAddr, OS_MEM_ARITH_E enArith);
//extern UINT32 osCreateDefDynPt();
//extern UINT32 osCreateDefMcDynPt();

#define TST_TSK_PRIOR_HIGH1            OS_TSK_PRIORITY_24
#define TST_TSK_PRIOR_LOW1             OS_TSK_PRIORITY_26

#define OS_LMSG_SIZE                    10
#define OS_SMSG_SIZE                    8

#define OS_MSG_HEAD_LEN            sizeof(MSG_HEAD_S)

//extern UINT8  m_aucMemRegion[0x50000];

#define TEST_STACK_SIZE       0x0800
#define PER_TEST_TIMES 100
#define OS_HUNT_NO_THREAD 0xffffffff
//UINT8 uniMsg_PtCreate_LcDyn = 0;
//UINT8 uniMsg_PtCreate_McDyn = 0;

UINT32  g_uwHighTaskPID;
UINT32  g_uwLowTaskPID;
UINT32  g_uwTestTskHdl;
UINT32  g_uwAllocMcmemFlag;
//extern UINT8 m_aucMemRegion02[UT_MEM_DYNAMIC_PT_SIZE] ;   /* ˽�ж�̬Page�ڴ����(ȱʡ)   */
//extern UINT8 m_aucMemRegion03[UT_MEM_MCDYNAMIC_PT_SIZE] ;   /* ����̬Pool�ڴ����(ȱʡ)   */

#define UT_HWI_EVENT_C_1 7

extern UINT8 osMsgSubmit(MSG_HANDLE_T uwMsgHandle,UINT32 uwThreadID,UINT8 ucPrio,UINT8 ucQid);

extern UINT32 osMcComEnQ(UINT32 uwDstPid, UINT8  ucOprtType, UINT32 uwOprtNum);

#define ASSERT_CONDITION(b)  (b)

/******************************************************��׮����******************************************************/
VOID * Stub_uniMemAllocxx(UINT32 uwMid, UINT8 ucPtNo, UINT32 uwSize)
{
    return NULL;
}


#if 0
OS_SEC_TEXT3_UT UINT32 UT_SRE_Msg_PtCreate(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA  stPara;
    if (!m_astMemPtInfo[UT_MEM_DEFAULT_LCDYN_PT].bInstalled)
    {
        stPara.ausSliceSize[0]=32;
        stPara.ausSliceSize[1]=48;
        stPara.ausSliceSize[2]=64;
        stPara.ausSliceSize[3]=128;
        stPara.ausSliceSize[4]=256;
        stPara.ausSliceSize[5]=512;
        stPara.ausSliceSize[6]=1024;
        stPara.ausSliceSize[7]=2048;

        stPara.bCachable = TRUE;

        stPara.enArith  = MEM_ARITH_POOL;
        stPara.pPtAddr  = &m_aucMemRegion02[0];
        stPara.uwPtSize = UT_MEM_DYNAMIC_PT_SIZE;

        uwRet = SRE_MemPtCreate(&stPara, UT_MEM_DEFAULT_LCDYN_PT);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

        uniMsg_PtCreate_LcDyn = 1;
    }

    if (!m_astMemPtInfo[UT_MEM_DEFAULT_MCDYN_PT].bInstalled)
    {
        stPara.ausSliceSize[0]=32;
        stPara.ausSliceSize[1]=48;
        stPara.ausSliceSize[2]=64;
        stPara.ausSliceSize[3]=128;
        stPara.ausSliceSize[4]=256;
        stPara.ausSliceSize[5]=512;
        stPara.ausSliceSize[6]=1024;
        stPara.ausSliceSize[7]=2048;
        /* ���ӿ�cache�������� */
        stPara.bCachable = TRUE;

        stPara.enArith  = MEM_ARITH_MCPOOL;
        stPara.pPtAddr  = &m_aucMemRegion03[0];;
        stPara.uwPtSize = UT_MEM_MCDYNAMIC_PT_SIZE;

        uwRet = SRE_MemPtCreate(&stPara, UT_MEM_DEFAULT_MCDYN_PT);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

        uniMsg_PtCreate_McDyn = 1;
    }
    return SRE_OK;
}

OS_SEC_TEXT3_UT VOID UT_uniMsg_PtDelete(void)
{
    if (1 == uniMsg_PtCreate_LcDyn)
    {
        m_astMemPtInfo[UT_MEM_DEFAULT_LCDYN_PT].bInstalled = FALSE;
    }
    if (1 == uniMsg_PtCreate_McDyn)
    {
        m_astMemPtInfo[UT_MEM_DEFAULT_MCDYN_PT].bInstalled = FALSE;
    }
}
#endif
OS_SEC_TEXT3_UT VOID TST_MsgRecEntry()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    (VOID)__SRE_MsgReceive(OS_WAIT_FOREVER, NULL, NULL);

    (VOID)__SRE_TaskResume(g_uwTestTskHdl);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT3_UT VOID TST_HighNoPayTskEntry()
{
    UINT32 uwMsgID;
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwMsgID = 20;
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, g_uwLowTaskPID,0);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_TaskSelf(&g_uwHighTaskPID);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT3_UT VOID TST_HighSmsgTskEntry()
{
    UINT32 uwMsgID;
    UINT16 usSize;
    UINT32 uwHandle;
    UINT32 uwRet;
    UINT32 uwTaskPID;

    usSize = OS_SMSG_SIZE;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_TRACK_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    memset((VOID *)uwHandle, 20, usSize);

    uwMsgID = 20;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwLowTaskPID,0);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_TaskSelf(&g_uwHighTaskPID);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT3_UT VOID TST_HighLmsgTskEntry()
{
    UINT32 uwMsgID;
    UINT16 usSize;
    UINT32 uwHandle;
    UINT32 uwRet;
    UINT32 uwTaskPID;

    usSize = OS_LMSG_SIZE;
    if(0 == g_uwAllocMcmemFlag)
    {
        uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
        ICUNIT_TRACK_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);
    }
    else
    {
        uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_MCDYN_PT,usSize,5);
        ICUNIT_TRACK_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);
    }
    memset((VOID *)uwHandle, 20, usSize);

    uwMsgID = 20;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwLowTaskPID,0);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_TaskSelf(&g_uwHighTaskPID);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT3_UT VOID TST_LowTskEntry()
{
    MSG_HANDLE_T uwHandle;
    UINT32 uwMsgID;
    UINT32 uwRet;
    UINT16 usSize;
    MSG_PID_T uwSenderPID;
    UINT32 uwTaskPID;

    /*���յ�һ����Ϣ*/
    uwHandle = __SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_TRACK_EQUAL(uwMsgID, 10, uwMsgID);
    ICUNIT_TRACK_EQUAL(uwSenderPID, g_uwTestTskHdl, uwSenderPID);
    if(uwHandle)
    {
        ICUNIT_TRACK_EQUAL(*(UINT8 *)uwHandle, 10, *(UINT8 *)uwHandle);

        usSize = SRE_MsgLength(uwHandle);
        memset((VOID *)uwHandle, 0, usSize);

        uwRet = SRE_MsgFree(uwHandle);
        ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
    }

    /*���յڶ�����Ϣ*/
    (VOID)__SRE_HuntByName(SRE_GetCoreID(),"TstHighTask", &g_uwHighTaskPID);
    uwHandle = __SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_TRACK_EQUAL(uwMsgID, 20, uwMsgID);
    ICUNIT_TRACK_EQUAL(uwSenderPID, g_uwHighTaskPID, uwSenderPID);
    if(uwHandle)
    {
        ICUNIT_TRACK_EQUAL(*(UINT8 *)uwHandle, 20, *(UINT8 *)uwHandle);

        usSize = SRE_MsgLength(uwHandle);
        memset((VOID *)uwHandle, 0, usSize);

        uwRet = SRE_MsgFree(uwHandle);
        ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
    }

    (VOID)__SRE_TaskResume(g_uwTestTskHdl);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

}

  #if 0
/**
*-@test  UT_SRE_MsgSend_001
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ƿ����
*-@tprecon
*-@tbrief
1.ָ���̷߳�����Ϣ�������uwMsgHandleΪOS_MSG_NO_PAYLOAD����Ч��Ŀ���߳����
*-@texpect
1.��Ϣ����ʧ�ܣ����ش�����OS_ERRNO_MSG_PID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_001(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT32  uwDstPID;

    uwMsgID = 0;
    uwDstPID = COMPOSE_PID(SRE_GetMaxNumberOfCores(), 0);
    uwRet = __SRE_MsgSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwDstPID);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MSG_PID_INVALID, uwRet);

    return SRE_OK;
}
#endif

/**
*-@test  UT_SRE_MsgSend_002
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ƿ����
*-@tprecon
*-@tbrief
1.Ŀ�����񴴽�ʱ��Ϣ���и���Ϊ��
2.�����uwMsgHandleΪOS_MSG_NO_PAYLOAD��Ŀ���̵߳�PID�����SRE_HuntByName�ӿڻ��
*-@texpect
1.Ŀ�����񴴽��ɹ�
1.������Ϣʧ�ܣ����ش�����OS_ERRNO_MSG_QID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_002(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 0;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_MSG_QID_INVALID, uwRet,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgSend_003
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ϸ�����
*-@tprecon
*-@tbrief
1.����һ�������ȼ�����
2.��ȡ������PID
3.�ڲ��������з���һ��������Ϣ����Ϣ�������ȼ�����
4.�������������
5.���ȼ�������յ����������͵���Ϣ��
*-@texpect
1.����һ�������ȼ�����ɹ�
2.��ȡ������PID�ɹ�
3.�ڲ��������з���һ��������Ϣ����Ϣ�������ȼ�����ɹ�
4.�������������ɹ�
5.���ȼ�������յ����������͵���Ϣ��ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_003(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID = 0;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 1;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskSuspend(g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
	uwRet = __SRE_TaskDelete(uwTaskID);
	ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

#if 0
/**
*-@test  UT_SRE_MsgSend_004
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.���볤��Ϣ����
2.�����uwMsgHandleΪ������Ϣ�巵�صľ������Ч��Ŀ���߳����
*-@texpect
1.������Ϣ�����ɹ�
2.��Ϣ����ʧ�ܣ����ش�����OS_ERRNO_MSG_PID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_004(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    UINT32 uwHandle;
    UINT16 usSize;
    UINT32 uwDstPID;

    usSize = OS_LMSG_SIZE;
    uwHandle = (UINT32)SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwDstPID = COMPOSE_PID(SRE_GetMaxNumberOfCores(), 0);

    uwRet = __SRE_MsgSend(uwHandle, uwMsgID, uwDstPID);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_PID_INVALID, uwRet, EXIT);

EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgSend_005
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.�������Ϣ����
2.�����uwMsgHandleΪ������Ϣ�巵�صľ������Ч��Ŀ���߳����
*-@texpect
1.������Ϣ�����ɹ�
2.��Ϣ����ʧ�ܣ����ش�����OS_ERRNO_MSG_PID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_005(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    UINT32 uwHandle;
    UINT16 usSize;
    UINT32 uwDstPID;

    usSize = OS_SMSG_SIZE;
    uwHandle = (UINT32)SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwDstPID = COMPOSE_PID(SRE_GetMaxNumberOfCores(), 0);

    uwRet = __SRE_MsgSend(uwHandle, uwMsgID, uwDstPID);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_PID_INVALID, uwRet, EXIT);

EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}
#endif
/**
*-@test  UT_SRE_MsgSend_006
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ƿ����
*-@tprecon
*-@tbrief
1.Ŀ�����񴴽�ʱ��Ϣ���и���Ϊ��
2.�������Ϣ����
3.Ŀ���̵߳�PID�����SRE_HuntByName�ӿڻ��
*-@texpect
1.Ŀ�����񴴽��ɹ�
2.�������Ϣ�����ɹ�
3.������Ϣʧ�ܣ����ش�����OS_ERRNO_MSG_QID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_006(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    UINT32 uwHandle;
    UINT16 usSize;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask6";
    stInitParam.usQNum       = 0;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask6", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    usSize = OS_SMSG_SIZE;
    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet, EXIT2);

EXIT2:

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgSend_007
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ƿ����
*-@tprecon
*-@tbrief
1.Ŀ�����񴴽�ʱ��Ϣ���и���Ϊ��
2.���볤��Ϣ����
3.Ŀ���̵߳�PID�����SRE_HuntByName�ӿڻ��
*-@texpect
1.Ŀ�����񴴽��ɹ�
2.���볤��Ϣ�����ɹ�
3.������Ϣʧ�ܣ����ش�����OS_ERRNO_MSG_QID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_007(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    UINT32 uwHandle;
    UINT16 usSize;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 0;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    usSize = OS_LMSG_SIZE;
    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet, EXIT2);

EXIT2:

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgSend_008
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ƿ����
*-@tprecon
*-@tbrief
1.�������Ϣ����uwMsgHandle��ΪOS_MSG_NO_PAYLOAD��Ҳ����������Ϣ���ڴ淵�صľ��ֵ��
2.��������ʱ���������Ϣ���и���������
3.Ŀ���̵߳�PID�����SRE_HuntByName�ӿڻ��
*-@texpect
1.�����ڴ�ɹ�
2.��������ɹ�
3.��Ϣ����ʧ�ܣ����ش�����OS_ERRNO_MSG_HANDLE_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_008(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    VOID * pAddr;
    UINT32 uwSize;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 1;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwSize = 10;
    pAddr = SRE_MemAllocAlign(OS_MID_MSG, OS_MEM_DEFAULT_LCDYN_PT, uwSize, MEM_ADDR_ALIGN_032);
    ICUNIT_GOTO_NOT_EQUAL((UINT32 *)pAddr, NULL, (UINT32 *)pAddr, EXIT1);

    uwRet = __SRE_MsgQSend((UINT32)pAddr, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_HANDLE_INVALID, uwRet, EXIT2);

EXIT2:

    uwRet = SRE_MemFree(OS_MID_MSG, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgSend_009
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ϸ�����
*-@tprecon
*-@tbrief
1.����һ�������ȼ�����
2.��ȡ������PID
3.�ڲ��������з���һ������Ϣ�������ȼ�����
4.�������������
5.���ȼ�������յ����������͵���Ϣ��
*-@texpect
1.����һ�������ȼ�����ɹ�
2.��ȡ������PID�ɹ�
3.�ڲ��������з���һ������Ϣ�������ȼ�����ɹ�
4.�������������ɹ�
5.���ȼ�������յ����������͵���Ϣ��ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_009(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID = 0;
    UINT32  uwTaskID;
    UINT16  usSize;
    MSG_HANDLE_T  uwHandle;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 1;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT1);

    usSize = OS_SMSG_SIZE;
    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT2);

    uwRet = __SRE_TaskSuspend(g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT2);

EXIT2:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgSend_010
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̷߳�����Ϣ������Ϸ�����
*-@tprecon
*-@tbrief
1.����һ�������ȼ�����
2.��ȡ������PID
3.�ڲ��������з���һ������Ϣ�������ȼ�����
4.�������������
5.���ȼ�������յ����������͵���Ϣ��
*-@texpect
1.����һ�������ȼ�����ɹ�
2.��ȡ������PID�ɹ�
3.�ڲ��������з���һ������Ϣ�������ȼ�����ɹ�
4.�������������ɹ�
5.���ȼ�������յ����������͵���Ϣ��ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgSend_010(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID = 0;
    UINT32  uwTaskID;
    MSG_HANDLE_T  uwHandle;
    UINT16  usSize;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 1;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT1);

    usSize = OS_LMSG_SIZE;
    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT2);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT2);

    uwRet = __SRE_TaskSuspend(g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT2);

EXIT2:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

#if 0
/**
*-@test  UT_SRE_MsgQSend_001
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.�����uwMsgHandleΪOS_MSG_NO_PAYLOAD����Ч��Ŀ���߳����
*-@texpect
2.��Ϣ����ʧ�ܣ����ش�����OS_ERRNO_MSG_PID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_001(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT32  uwDstPID;

    uwMsgID = 0;
    uwDstPID = COMPOSE_PID(SRE_GetMaxNumberOfCores(), 0);
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwDstPID,0);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MSG_PID_INVALID, uwRet);

    return SRE_OK;
}
#endif
/**
*-@test  UT_SRE_MsgQSend_002
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.��������ʱ����Ϣ���и���Ϊ��
2.Ŀ���̵߳�PID��SRE_HuntByName�ӿڻ�ȡ
3.������Ϣ�������uwMsgHandleΪOS_MSG_NO_PAYLOAD��������Ч��PID
*-@texpect
1.���񴴽��ɹ�
2.Ŀ���̵߳�PID��SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.������Ϣʧ�ܣ����ش�����OS_ERRNO_MSG_QID_INVALIDD
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_002(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 0;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_MSG_QID_INVALID, uwRet,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_003
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.��������ʱ����Ϣ���и���������
2.Ŀ���̵߳�PID��SRE_HuntByName�ӿڻ�ȡ
3.������Ϣ�������uwMsgHandleΪOS_MSG_NO_PAYLOAD��������Ч��PID�������QID�Ŵ��ڵ������񴴽�ʱ�Ķ��и���
*-@texpect
1.���񴴽��ɹ�
2.Ŀ���̵߳�PID��SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.������Ϣʧ�ܣ����ش�����OS_ERRNO_MSG_QID_INVALIDD
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_003(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 1;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTskHdl, 1);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_MSG_QID_INVALID, uwRet,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_004
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ������Ϸ�����
*-@tprecon
*-@tbrief
1.��������ʱ����Ϣ���и���������
2.Ŀ���̵߳�PID��SRE_HuntByName�ӿڻ�ȡ
3.������Ϣ�������uwMsgHandleΪOS_MSG_NO_PAYLOAD��������Ч��PID�������QID��С�����񴴽�ʱ�Ķ��и���
*-@texpect
1.���񴴽��ɹ�
2.Ŀ���̵߳�PID��SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.������Ϣ�ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_004(void)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 1;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskSuspend(g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}
#if 0
/**
*-@test  UT_SRE_MsgQSend_005
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.�������Ϣ����
2.�����uwMsgHandleΪ������Ϣ�巵�صľ������Ч��Ŀ���߳����
*-@texpect
1.������Ϣ�����ɹ�
2.��Ϣ����ʧ�ܣ����ش�����OS_ERRNO_MSG_PID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_005(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    UINT32 uwHandle;
    UINT16 usSize;
    UINT32 uwDstPID;

    usSize = OS_SMSG_SIZE;
    uwHandle = (UINT32)SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwDstPID = COMPOSE_PID(SRE_GetMaxNumberOfCores(), 0);
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, uwDstPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_PID_INVALID, uwRet, EXIT);

EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_006
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.���볤��Ϣ����
2.�����uwMsgHandleΪ������Ϣ�巵�صľ������Ч��Ŀ���߳����
*-@texpect
1.������Ϣ�����ɹ�
2.��Ϣ����ʧ�ܣ����ش�����OS_ERRNO_MSG_PID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_006(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    UINT32 uwHandle;
    UINT16 usSize;
    UINT32 uwDstPID;

    usSize = OS_LMSG_SIZE;
    uwHandle = (UINT32)SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_ASSERT_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwDstPID = COMPOSE_PID(SRE_GetMaxNumberOfCores(), 0);
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, uwDstPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_PID_INVALID, uwRet, EXIT);

EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}
#endif
/**
*-@test  UT_SRE_MsgQSend_007
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.Ŀ�����񴴽�ʱ��Ϣ���и���Ϊ��
2.�������Ϣ����
3.Ŀ���̵߳�PID�����SRE_HuntByName�ӿڻ��
*-@texpect
1.Ŀ�����񴴽��ɹ�
2.�������Ϣ�����ɹ�
3.������Ϣʧ�ܣ����ش�����OS_ERRNO_MSG_QID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_007(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    UINT32 uwHandle;
    UINT16 usSize;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 0;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usSize = OS_SMSG_SIZE;
    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, uwTskHdl,0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet, EXIT2);

EXIT2:

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_008
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ������Ƿ�����
*-@tprecon
*-@tbrief
1.Ŀ�����񴴽�ʱ��Ϣ���и���Ϊ��
2.���볤��Ϣ����
3.Ŀ���̵߳�PID�����SRE_HuntByName�ӿڻ��
*-@texpect
1.Ŀ�����񴴽��ɹ�
2.���볤��Ϣ�����ɹ�
3.������Ϣʧ�ܣ����ش�����OS_ERRNO_MSG_QID_INVALID
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_008(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID = 0;
    UINT32 uwHandle;
    UINT16 usSize;
    UINT32  uwTaskID;
    TSK_HANDLE_T uwTskHdl;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MsgRecEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask1";
    stInitParam.usQNum       = 0;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstTask1", &uwTskHdl);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usSize = OS_SMSG_SIZE;
    uwHandle = (UINT32)__SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, uwTskHdl,0);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet, EXIT2);

EXIT2:

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_009
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ���������
*-@tprecon
*-@tbrief
1.����һ�����ڲ����������ȼ���������Ϣ���и�������0
2.����һ�����ڲ����������ȼ���������Ϣ���и�������0
3.��������������ȼ�������һ��������Ϣ������Ϣ
4.�л��������ȼ������ڸ����ȼ��������ٴ�������ȼ�������һ��������Ϣ������Ϣ
5.�ȴ���ǰһ����Ϣ
6.�ٴ����һ����Ϣ
*-@texpect
1.�����ȼ����񴴽��ɹ�
2.�����ȼ����񴴽��ɹ�
3.��������������ȼ���������Ϣ�ɹ�
4.�����ȼ�����������ȼ���������Ϣ�ɹ�
5.�ȴ���ǰһ����Ϣ�ɹ�
6.�ٴ����һ����Ϣ�ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_009(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINT32  uwHighTaskID;
    UINT32  uwLowTaskID;
    TSK_INIT_PARAM_S stInitParamHigh;
    TSK_INIT_PARAM_S stInitParamLow;

    memset((VOID*)&stInitParamHigh, 0, sizeof(stInitParamHigh));
    memset((VOID*)&stInitParamLow, 0, sizeof(stInitParamLow));

    stInitParamLow.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_LowTskEntry;
    stInitParamLow.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParamLow.uwStackSize  = 0;
    stInitParamLow.pcName       = "TstLowTask";
    stInitParamLow.usQNum       = 1;
    stInitParamLow.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwLowTaskID, &stInitParamLow);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstLowTask", &g_uwLowTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, g_uwLowTaskPID,0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    stInitParamHigh.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_HighNoPayTskEntry;
    stInitParamHigh.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParamHigh.uwStackSize  = 0;
    stInitParamHigh.pcName       = "TstHighTask";
    stInitParamHigh.usQNum       = 1;

    uwRet = __SRE_TaskCreate(&uwHighTaskID, &stInitParamHigh);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT2);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT2:
    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwHighTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_010
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ���������
*-@tprecon
*-@tbrief
1.����һ�����ڲ����������ȼ���������Ϣ���и�������0
2.����һ�����ڲ����������ȼ���������Ϣ���и�������0
3.ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�
4.��������������ȼ�������һ������Ϣ
5.�л��������ȼ������ڸ����ȼ�������ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�
6.�ڸ����ȼ��������ٴ�������ȼ�������һ������Ϣ
7.�ȴ���ǰһ����Ϣ
8.�ٴ����һ����Ϣ
*-@texpect
1.�����ȼ����񴴽��ɹ�
2.�����ȼ����񴴽��ɹ�
3.ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�ɹ�
4.��������������ȼ���������Ϣ�ɹ�
5.�л��������ȼ������ڸ����ȼ�������ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�ɹ�
6.�����ȼ�����������ȼ���������Ϣ�ɹ�
7.�ȴ���ǰһ����Ϣ�ɹ�
8.�ٴ����һ����Ϣ�ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_010(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINT16 usSize;
    UINT32  uwHighTaskID;
    UINT32  uwLowTaskID;
    MSG_HANDLE_T uwHandle;
    TSK_INIT_PARAM_S stInitParamHigh;
    TSK_INIT_PARAM_S stInitParamLow;

    memset((VOID*)&stInitParamHigh, 0, sizeof(stInitParamHigh));
    memset((VOID*)&stInitParamLow, 0, sizeof(stInitParamLow));

    stInitParamLow.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_LowTskEntry;
    stInitParamLow.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParamLow.uwStackSize  = 0;
    stInitParamLow.pcName       = "TstLowTask";
    stInitParamLow.usQNum       = 1;
    stInitParamLow.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwLowTaskID, &stInitParamLow);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstLowTask", &g_uwLowTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    usSize = OS_SMSG_SIZE;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT, usSize, 5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    memset((VOID *)uwHandle, 10, usSize);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwLowTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT2);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT2);

    stInitParamHigh.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_HighSmsgTskEntry;
    stInitParamHigh.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParamHigh.uwStackSize  = 0;
    stInitParamHigh.pcName       = "TstHighTask";
    stInitParamHigh.usQNum       = 1;

    uwRet = __SRE_TaskCreate(&uwHighTaskID, &stInitParamHigh);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT3);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT3:

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwHighTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT2:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_011
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ���������
*-@tprecon
*-@tbrief
1.����һ�����ڲ����������ȼ���������Ϣ���и�������0
2.����һ�����ڲ����������ȼ���������Ϣ���и�������0
3.ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�
4.��������������ȼ�������һ������Ϣ
5.�л��������ȼ������ڸ����ȼ�������ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�
6.�ڸ����ȼ��������ٴ�������ȼ�������һ������Ϣ
7.�ȴ���ǰһ����Ϣ
8.�ٴ����һ����Ϣ
*-@texpect
1.�����ȼ����񴴽��ɹ�
2.�����ȼ����񴴽��ɹ�
3.ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�ɹ�
4.��������������ȼ���������Ϣ�ɹ�
5.�л��������ȼ������ڸ����ȼ�������ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�ɹ�
6.�����ȼ�����������ȼ���������Ϣ�ɹ�
7.�ȴ���ǰһ����Ϣ�ɹ�
8.�ٴ����һ����Ϣ�ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_011(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINT16 usSize;
    UINT32  uwHighTaskID;
    UINT32  uwLowTaskID;
    MSG_HANDLE_T uwHandle;
    TSK_INIT_PARAM_S stInitParamHigh;
    TSK_INIT_PARAM_S stInitParamLow;

    g_uwAllocMcmemFlag = 0;

    memset((VOID*)&stInitParamHigh, 0, sizeof(stInitParamHigh));
    memset((VOID*)&stInitParamLow, 0, sizeof(stInitParamLow));

    stInitParamLow.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_LowTskEntry;
    stInitParamLow.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParamLow.uwStackSize  = 0;
    stInitParamLow.pcName       = "TstLowTask";
    stInitParamLow.usQNum       = 1;
    stInitParamLow.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwLowTaskID, &stInitParamLow);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstLowTask", &g_uwLowTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    usSize = OS_LMSG_SIZE;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    memset((VOID *)uwHandle, 10, usSize);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwLowTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT2);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT2);

    stInitParamHigh.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_HighLmsgTskEntry;
    stInitParamHigh.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParamHigh.uwStackSize  = 0;
    stInitParamHigh.pcName       = "TstHighTask";
    stInitParamHigh.usQNum       = 1;

    uwRet = __SRE_TaskCreate(&uwHighTaskID, &stInitParamHigh);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT3);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT3:

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwHighTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT2:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_012
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳���Ϣ���з�����Ϣ���������
*-@tprecon
*-@tbrief
1.����һ�����ڲ����������ȼ���������Ϣ���и�������0
2.����һ�����ڲ����������ȼ���������Ϣ���и�������0
3.ͨ������̬�ڴ�������Ϣ���ڴ�
4.��������������ȼ�������һ������Ϣ
5.�л��������ȼ������ڸ����ȼ�������ͨ������̬�ڴ�������Ϣ���ڴ�
6.�ڸ����ȼ��������ٴ�������ȼ�������һ������Ϣ
7.�ȴ���ǰһ����Ϣ
8.�ٴ����һ����Ϣ
*-@texpect
1.�����ȼ����񴴽��ɹ�
2.�����ȼ����񴴽��ɹ�
3.ͨ��˽�ж�̬�ڴ�������Ϣ���ڴ�ɹ�
4.��������������ȼ���������Ϣ�ɹ�
5.�л��������ȼ������ڸ����ȼ�������ͨ������̬�ڴ�������Ϣ���ڴ�ɹ�
6.�����ȼ�����������ȼ���������Ϣ�ɹ�
7.�ȴ���ǰһ����Ϣ�ɹ�
8.�ٴ����һ����Ϣ�ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_012(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINT16 usSize;
    UINT32  uwHighTaskID;
    UINT32  uwLowTaskID;
    MSG_HANDLE_T uwHandle;
    TSK_INIT_PARAM_S stInitParamHigh;
    TSK_INIT_PARAM_S stInitParamLow;

    g_uwAllocMcmemFlag = 0;

    memset((VOID*)&stInitParamHigh, 0, sizeof(stInitParamHigh));
    memset((VOID*)&stInitParamLow, 0, sizeof(stInitParamLow));

    stInitParamLow.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_LowTskEntry;
    stInitParamLow.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParamLow.uwStackSize  = 0;
    stInitParamLow.pcName       = "TstLowTask";
    stInitParamLow.usQNum       = 1;
    stInitParamLow.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwLowTaskID, &stInitParamLow);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TstLowTask", &g_uwLowTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

    usSize = OS_LMSG_SIZE;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_MCDYN_PT,usSize,5);
    ICUNIT_GOTO_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle,EXIT1);

    memset((VOID *)uwHandle, 10, usSize);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwLowTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT2);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT2);

    stInitParamHigh.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_HighLmsgTskEntry;
    stInitParamHigh.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParamHigh.uwStackSize  = 0;
    stInitParamHigh.pcName       = "TstHighTask";
    stInitParamHigh.usQNum       = 1;

    uwRet = __SRE_TaskCreate(&uwHighTaskID, &stInitParamHigh);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT3);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT3:

    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwHighTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT2:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT1:
    uwRet = __SRE_TaskDelete(uwLowTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_013
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ָ���̵߳����жϷ�����Ϣ����ȷ���
*-@tprecon
*-@tbrief
1.������һ�����ж�
2.Ŀ�����жϵ�PID�����SRE_HuntByName�ӿڻ�ȡ
3.�������Ϣ����uwMsgHandleΪOS_MSG_NO_PAYLOAD
*-@texpect
1.������һ�����жϳɹ�
2.Ŀ�����жϵ�PID�����SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.��Ϣ���ͳɹ�
*-@tprior  1
*-@tremark
*/

OS_SEC_TEXT3_UT VOID UT_SRE_MsgQReceive_13_SWI(UINT32 uwValue)
{
    UINT32  uwMsgID;

    (VOID)__SRE_MsgReceive(OS_NO_WAIT, &uwMsgID, NULL);
    ICUNIT_TRACK_EQUAL(uwMsgID, 10, uwMsgID);
}

OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_013(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINT32  uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    memset((VOID*)&stInitPara, 0, sizeof(stInitPara));

    stInitPara.pcSwiName = "msgTestswi";
    stInitPara.pfnHandler = UT_SRE_MsgQReceive_13_SWI;
    stInitPara.usPriority = OS_SWI_PRIORITY_06;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwSwiID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_014
*-@tspec  ��Ϣģ��UT����
*-@ttitle  �����ж���ָ���̷߳�����Ϣ����ȷ���
*-@tprecon
*-@tbrief
1.����һ�����ж�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ
3.�����ж��������Ϣ���������Ϣ����uwMsgHandleΪOS_MSG_NO_PAYLOAD
4.�������������õȴ���ʽ������Ϣ
*-@texpect
1.����һ�����жϳɹ�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.��Ϣ���ͳɹ�
4.�������������õȴ���ʽ���ճɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT VOID UT_SRE_MsgQSend_14_SWI(UINT32 uwValue)
{
    UINT32  uwRet;
    UINT32  uwMsgID;

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, g_uwTestTskHdl, 0);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
}

OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_014(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINT32  uwSwiID;
    MSG_PID_T uwSenderPID;
    SWI_INIT_PARA_S stInitPara;

    memset((VOID*)&stInitPara, 0, sizeof(stInitPara));

    stInitPara.pcSwiName = "msgTestswi";
    stInitPara.pfnHandler = UT_SRE_MsgQSend_14_SWI;
    stInitPara.usPriority = OS_SWI_PRIORITY_06;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    (VOID)__SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_GOTO_EQUAL(uwMsgID, 10, uwMsgID, EXIT);
    ICUNIT_GOTO_EQUAL(uwSenderPID, uwSwiID, uwSenderPID, EXIT);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_015
*-@tspec  ��Ϣģ��UT����
*-@ttitle  �����ж���ָ���̷߳�����Ϣ����ȷ���
*-@tprecon
*-@tbrief
1.����һ�����ж�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ
3.�����ж��������Ϣ���������Ϣ����uwMsgHandleΪ�������Ϣ���صľ��
4.�������������õȴ���ʽ������Ϣ
*-@texpect
1.����һ�����жϳɹ�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.��Ϣ���ͳɹ�
4.�������������õȴ���ʽ���ճɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT VOID UT_SRE_MsgQSend_15_SWI(UINT32 uwValue)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT16  usSize;
    UINT32  uwHandle;

    usSize = OS_SMSG_SIZE;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_TRACK_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwTestTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    return;
EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
}

OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_015(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINT32  uwSwiID;
    MSG_PID_T uwSenderPID;
    SWI_INIT_PARA_S stInitPara;

    memset((VOID*)&stInitPara, 0, sizeof(stInitPara));

    stInitPara.pcSwiName = "msgTestswi";
    stInitPara.pfnHandler = UT_SRE_MsgQSend_15_SWI;
    stInitPara.usPriority = OS_SWI_PRIORITY_06;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    (VOID)__SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_GOTO_EQUAL(uwMsgID, 10, uwMsgID, EXIT);
    ICUNIT_GOTO_EQUAL(uwSenderPID, uwSwiID, uwSenderPID, EXIT);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_016
*-@tspec  ��Ϣģ��UT����
*-@ttitle  �����ж���ָ���̷߳�����Ϣ����ȷ���
*-@tprecon
*-@tbrief
1.����һ�����ж�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ
3.�����ж��������Ϣ���������Ϣ����uwMsgHandleΪ���볤��Ϣ���صľ��
4.�������������õȴ���ʽ������Ϣ
*-@texpect
1.����һ�����жϳɹ�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.��Ϣ���ͳɹ�
4.�������������õȴ���ʽ���ճɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT VOID UT_SRE_MsgQSend_16_SWI(UINT32 uwValue)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT16  usSize;
    UINT32  uwHandle;

    usSize = OS_SMSG_SIZE;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_TRACK_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwTestTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    return;
EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
}

OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_016(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINT32  uwSwiID;
    MSG_PID_T uwSenderPID;
    SWI_INIT_PARA_S stInitPara;

    memset((VOID*)&stInitPara, 0, sizeof(stInitPara));

    stInitPara.pcSwiName = "msgTestswi";
    stInitPara.pfnHandler = UT_SRE_MsgQSend_16_SWI;
    stInitPara.usPriority = OS_SWI_PRIORITY_06;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(),"TestTask", &g_uwTestTskHdl);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    (VOID)__SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_GOTO_EQUAL(uwMsgID, 10, uwMsgID, EXIT);
    ICUNIT_GOTO_EQUAL(uwSenderPID, uwSwiID, uwSenderPID, EXIT);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}
/**
*-@test  UT_SRE_MsgQSend_017
*-@tspec  ��Ϣģ��UT����
*-@ttitle  Ӳ�ж���ָ�������̷߳�����Ϣ����ȷ���
*-@tprecon
*-@tbrief
1.����һ��Ӳ�ж�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ
3.ʹ�ò�����Ӳ�ж�
4.�������Ϣ����uwMsgHandleΪOS_MSG_NO_PAYLOAD
5.�����������õȴ���ʽ������Ϣ
*-@texpect
1.����һ��Ӳ�жϳɹ�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.ʹ�ò�����Ӳ�жϳɹ�
4.��Ϣ���ͳɹ�
5.�����������õȴ���ʽ������Ϣ�ɹ�
*-@tprior  1
*-@tremark
*/

OS_SEC_TEXT3_UT VOID UT_SRE_MsgQSend_17_HWI(UINT32 uwValue)
{
    UINT32  uwRet;
    UINT32  uwMsgID;

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, g_uwTestTskHdl, 0);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
}

OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_017(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINTPTR uvIER;
    HWI_HANDLE_T uwHwiNum = UT_HWI_EVENT_C_1;
    HWI_PRIOR_T usHwiPrio = UT_HWI_PRIO_0;
    UINT32 uwHwiMode;
    MSG_PID_T uwSenderPID;

    uwHwiMode = OS_HWI_MODE_COMBINE;
    //uwRet = SRE_HwiSetAttr(uwHwiNum, usHwiPrio, uwHwiMode);
    //ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwRet = __SRE_HwiCreate(uwHwiNum,usHwiPrio,IT_HWI_SECURE_MODE, UT_SRE_MsgQSend_17_HWI, uwHwiNum);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uvIER = __SRE_HwiEnable(uwHwiNum);

    uwRet = __SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), uwHwiNum);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_GOTO_EQUAL(uwMsgID, 10, uwMsgID, EXIT);
    ICUNIT_GOTO_EQUAL(uwSenderPID, COMPOSE_PID(SRE_GetCoreID(), 0xff), uwSenderPID, EXIT);

EXIT:
   // SRE_HwiRestore(uwHwiNum, uvIER);
    uwRet = __SRE_HwiDelete(uwHwiNum);
    ICUNIT_TRACK_EQUAL(uwRet,SRE_OK,uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_018
*-@tspec  ��Ϣģ��UT����
*-@ttitle  Ӳ�ж���ָ�������̷߳�����Ϣ����ȷ���
*-@tprecon
*-@tbrief
1.����һ��Ӳ�ж�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ
3.ʹ�ò�����Ӳ�ж�
4.�������Ϣ����uwMsgHandleΪ�������Ϣ���صľ��
5.�����������õȴ���ʽ������Ϣ
*-@texpect
1.����һ��Ӳ�жϳɹ�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.ʹ�ò�����Ӳ�жϳɹ�
4.��Ϣ���ͳɹ�
5.�����������õȴ���ʽ������Ϣ�ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT VOID UT_SRE_MsgQSend_18_HWI(UINT32 uwValue)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT16  usSize;
    UINT32  uwHandle;

    usSize = OS_SMSG_SIZE;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_TRACK_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwTestTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    return;
EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
}
OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_018(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINTPTR uvIER;
    HWI_HANDLE_T uwHwiNum = UT_HWI_EVENT_C_1;
    HWI_PRIOR_T usHwiPrio = UT_HWI_PRIO_0;
    UINT32 uwHwiMode;
    MSG_PID_T uwSenderPID;

    uwHwiMode = OS_HWI_MODE_COMBINE;
    //uwRet = SRE_HwiSetAttr(uwHwiNum, usHwiPrio, uwHwiMode);
    //ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwRet = __SRE_HwiCreate(uwHwiNum,usHwiPrio,IT_HWI_SECURE_MODE, UT_SRE_MsgQSend_18_HWI, uwHwiNum);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uvIER = __SRE_HwiEnable(uwHwiNum);

    uwRet = __SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), uwHwiNum);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_GOTO_EQUAL(uwMsgID, 10, uwMsgID, EXIT);
    ICUNIT_GOTO_EQUAL(uwSenderPID, COMPOSE_PID(SRE_GetCoreID(), 0xff), uwSenderPID, EXIT);

EXIT:
  //  SRE_HwiRestore(uwHwiNum, uvIER);
    uwRet = __SRE_HwiDelete(uwHwiNum);
    ICUNIT_TRACK_EQUAL(uwRet,SRE_OK,uwRet);
    return SRE_OK;
}

/**
*-@test  UT_SRE_MsgQSend_019
*-@tspec  ��Ϣģ��UT����
*-@ttitle  Ӳ�ж���ָ�������̷߳�����Ϣ����ȷ���
*-@tprecon
*-@tbrief
1.����һ��Ӳ�ж�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ
3.ʹ�ò�����Ӳ�ж�
4.�������Ϣ����uwMsgHandleΪ���볤��Ϣ���صľ��
5.�����������õȴ���ʽ������Ϣ
*-@texpect
1.����һ��Ӳ�жϳɹ�
2.Ŀ�������̵߳�PID�����SRE_HuntByName�ӿڻ�ȡ�ɹ�
3.ʹ�ò�����Ӳ�жϳɹ�
4.��Ϣ���ͳɹ�
5.�����������õȴ���ʽ������Ϣ�ɹ�
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT VOID UT_SRE_MsgQSend_19_HWI(UINT32 uwValue)
{
    UINT32  uwRet;
    UINT32  uwMsgID;
    UINT16  usSize;
    UINT32  uwHandle;

    usSize = OS_LMSG_SIZE;
    uwHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,usSize,5);
    ICUNIT_TRACK_NOT_EQUAL(uwHandle, OS_MSG_CREATE_ERR, uwHandle);

    uwMsgID = 10;
    uwRet = __SRE_MsgQSend(uwHandle, uwMsgID, g_uwTestTskHdl, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    return;
EXIT:
    uwRet = SRE_MsgFree(uwHandle);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
}

OS_SEC_TEXT3_UT UINT32 UT_SRE_MsgQSend_019(void)
{
    UINT32 uwRet;
    UINT32 uwMsgID;
    UINTPTR uvIER;
    HWI_HANDLE_T uwHwiNum = UT_HWI_EVENT_C_1;
    HWI_PRIOR_T usHwiPrio = UT_HWI_PRIO_0;
    UINT32 uwHwiMode;
    MSG_PID_T uwSenderPID;

    uwHwiMode = OS_HWI_MODE_COMBINE;
    //uwRet = SRE_HwiSetAttr(uwHwiNum, usHwiPrio, uwHwiMode);
    //ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwRet = __SRE_HwiCreate(uwHwiNum,usHwiPrio,IT_HWI_SECURE_MODE, UT_SRE_MsgQSend_19_HWI, uwHwiNum);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uvIER = __SRE_HwiEnable(uwHwiNum);

    uwRet = __SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), uwHwiNum);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_MsgReceive(OS_WAIT_FOREVER, &uwMsgID, &uwSenderPID);
    ICUNIT_GOTO_EQUAL(uwMsgID, 10, uwMsgID, EXIT);
    ICUNIT_GOTO_EQUAL(uwSenderPID, COMPOSE_PID(SRE_GetCoreID(), 0xff), uwSenderPID, EXIT);

EXIT:
  //  SRE_HwiRestore(uwHwiNum, uvIER);
    uwRet = __SRE_HwiDelete(uwHwiNum);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

#if 0


/**
*-@test  UT_uniMsgSend_015
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣ��һ�����жϷ�������Ϣ����Ϣ!
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT VOID ut_UniMsg_15_SWI(UINT32 uwValue)
{
    UINT32  uwRet;
    UINT32 auwMsg[3];
    UINT32 uwType;

    uwRet = SRE_MsgQRecv((UINT32*)auwMsg, &uwType, NULL, 1, 0);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    g_uwUtCheckLc++;
    return;
}

OS_SEC_TEXT3_UT UINT32 UT_uniMsgSend_015()
{
    UINT32 uwRet;
    SWI_HANDLE_T puwSwiID;
    UINT32 auwMsg[3];
    SWI_INIT_PARA_S stInitPara;
    stInitPara.pcSwiName = "msgTestswi15";
    stInitPara.pfnHandler = ut_UniMsg_15_SWI;
    stInitPara.usPriority = OS_SWI_PRIORITY_06;
    stInitPara.uwInitValue = 0;

    g_uwUtCheckLc = 0;

    SRE_SwiCreate(&puwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_MsgSend((VOID *) auwMsg, 0, puwSwiID, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
    ICUNIT_GOTO_EQUAL(g_uwUtCheckLc, 1, g_uwUtCheckLc, EXIT1);

EXIT1:
    uwRet = SRE_SwiDelete(puwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}



/**
*-@test  UT_uniMsgReceive_001
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ����ղ��ԣ�ϵͳ״̬g_vuwUniFlagΪӲ�жϼ���
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgReceive_001(void)
{
    UINT32   uwMsgHdl;
    UINT32   uwIntSave;

    uwIntSave = __SRE_IntLock();
    g_vuwUniFlag |= OS_FLG_HWI_ACTIVE;

    uwMsgHdl = TS_SRE_MsgRecv(0x000000ff,0,0);
    ICUNIT_ASSERT_EQUAL(uwMsgHdl, OS_MSG_RECEIVE_ERR, uwMsgHdl);

    g_vuwUniFlag &= ~OS_FLG_HWI_ACTIVE;
    (VOID)__SRE_IntRestore(uwIntSave);

    return SRE_OK;
}

/**
*-@test  UT_uniMsgReceive_002
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ����ղ��ԣ�ϵͳ״̬g_vuwUniFlagΪ���жϼ���
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgReceive_002(void)
{
    UINT32    uwMsgHdl;

    SRE_TaskLock();

    uwMsgHdl = TS_SRE_MsgRecv(0x000000ff,0,0);
    ICUNIT_ASSERT_EQUAL(uwMsgHdl, OS_MSG_RECEIVE_ERR, uwMsgHdl);

    SRE_TaskUnlock();

    return SRE_OK;
}

/**
*-@test  UT_uniMsgSend_Free_001
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ����ղ��ԣ������ж��н�����Ϣ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgSend_Free_001_Func()
{
    UINT32 uwRet;
    UINT32 uwMsgHdl;
    UINT32 uwMsgID;
    MSG_PID_T uwSenderPID;

    uwMsgHdl = TS_SRE_MsgRecv(0xfffffffE,&uwMsgID,&uwSenderPID);
    ICUNIT_ASSERT_NOT_EQUAL(uwMsgHdl, OS_MSG_RECEIVE_ERR, uwMsgHdl);
    ICUNIT_ASSERT_EQUAL(uwMsgID, OS_MSG_PAYLOAD, uwMsgID);
    ICUNIT_ASSERT_EQUAL(uwSenderPID, g_puwTaskPID, uwSenderPID);

    if(0 != uwMsgHdl)
    {
        uwRet = SRE_MsgFree((VOID*)uwMsgHdl);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }

    return SRE_OK;
}

OS_SEC_TEXT3_UT UINT32 UT_uniMsgSend_Free_001()
{
    UINT32 uwRet;
    SWI_HANDLE_T uwSwiID;
    UINT32 uwSwiPID;
    MSG_HANDLE_T  uwRet1;
    SWI_INIT_PARA_S stSwiPara;

    stSwiPara.pcSwiName = "MsgSwi_901";
    stSwiPara.pfnHandler = (SWI_PROC_FUNC)UT_uniMsgSend_Free_001_Func;
    stSwiPara.usPriority = 15;
    stSwiPara.uwInitValue = 0xffffffff;

    uwRet1= (UINT32)SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,10,8);
    ICUNIT_ASSERT_NOT_EQUAL(uwRet1, OS_MSG_CREATE_ERR, uwRet1);

    uwRet = SRE_SwiCreate(&uwSwiID, &stSwiPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    SRE_HuntByName(SRE_GetCoreID(),"MsgSwi_901", &uwSwiPID);
    ICUNIT_ASSERT_NOT_EQUAL(uwSwiPID, OS_ERRNO_HUNT_THREAD_NOT_CREAT, uwSwiPID);

    g_puwTaskPID = 0;
    SRE_TaskSelf(&g_puwTaskPID);

    uwRet = __SRE_MsgSend((VOID*)uwRet1, OS_MSG_PAYLOAD, uwSwiPID, OS_MSG_NORMAL);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_SwiDelete(uwSwiID);

    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_uniMsgSend_Free_002
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ����ղ��ԣ������ж��н�����Ϣ��������ʽ����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgSend_Free_002_Func()
{
    UINT32 uwRet;
    UINT32    uwMsgHdl;
    UINT32 uwMsgID;
    MSG_PID_T uwSenderPID;

    uwMsgHdl = TS_SRE_MsgRecv(0xfffffffE,&uwMsgID,&uwSenderPID);
    ICUNIT_ASSERT_NOT_EQUAL(uwMsgHdl, OS_MSG_RECEIVE_ERR, uwMsgHdl);
    ICUNIT_ASSERT_EQUAL(uwMsgID, OS_MSG_PAYLOAD, uwMsgID);
    ICUNIT_ASSERT_EQUAL(uwSenderPID, g_puwTaskPID, uwSenderPID);

    if(0 != uwMsgHdl)
    {
        uwRet = SRE_MsgFree((VOID*)uwMsgHdl);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }

   return SRE_OK;
}

OS_SEC_TEXT3_UT UINT32 UT_uniMsgSend_Free_002()
{
    UINT32 uwRet;
    SWI_HANDLE_T           uwSwiID;
    UINT32 uwSwiPID;
    MSG_HANDLE_T  uwRet1;
    SWI_INIT_PARA_S stSwiPara;

    stSwiPara.pcSwiName = "MsgSwi_902";
    stSwiPara.pfnHandler = (SWI_PROC_FUNC)UT_uniMsgSend_Free_002_Func;
    stSwiPara.usPriority = 15;
    stSwiPara.uwInitValue = 0xffffffff;

    uwRet1= (UINT32)SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,10,8);
    ICUNIT_ASSERT_NOT_EQUAL(uwRet1, OS_MSG_CREATE_ERR, uwRet1);

    uwRet = SRE_SwiCreate(&uwSwiID, &stSwiPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    SRE_HuntByName(SRE_GetCoreID(),"MsgSwi_902", &uwSwiPID);
    ICUNIT_ASSERT_NOT_EQUAL(uwSwiPID, OS_ERRNO_HUNT_THREAD_NOT_CREAT, uwSwiPID);

    g_puwTaskPID = 0;
    SRE_TaskSelf(&g_puwTaskPID);

    uwRet = __SRE_MsgSend((VOID*)uwRet1, OS_MSG_PAYLOAD, uwSwiPID, OS_MSG_URGENT);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_uniMsgSend_Free_003
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ����ղ��ԣ����η��������ж��н�����Ϣ��������ʽ����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgSend_Free_003_Func()
{
    UINT32 uwRet;
    UINT32    uwMsgHdl;
    UINT32 uwMsgID;
    MSG_PID_T uwSenderPID;

    uwMsgHdl = TS_SRE_MsgRecv(0xfffffffE,&uwMsgID,&uwSenderPID);
    ICUNIT_ASSERT_NOT_EQUAL(uwMsgHdl, OS_MSG_RECEIVE_ERR, uwMsgHdl);
    ICUNIT_ASSERT_EQUAL(uwMsgID, OS_MSG_PAYLOAD, uwMsgID);
    ICUNIT_ASSERT_EQUAL(uwSenderPID, g_puwTaskPID, uwSenderPID);

    if(0 != uwMsgHdl)
    {
        uwRet = SRE_MsgFree((VOID*)uwMsgHdl);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    }

    return SRE_OK;
}

OS_SEC_TEXT3_UT UINT32 UT_uniMsgSend_Free_003()
{
    UINT32 uwRet;
    SWI_HANDLE_T           uwSwiID;
    UINT32 uwSwiPID;
    MSG_HANDLE_T  uwRet1;
    SWI_INIT_PARA_S stSwiPara;

    stSwiPara.pcSwiName = "MsgSwi_903";
    stSwiPara.pfnHandler = (SWI_PROC_FUNC)UT_uniMsgSend_Free_003_Func;
    stSwiPara.usPriority = 15;
    stSwiPara.uwInitValue = 0xffffffff;

    uwRet1= (UINT32)SRE_MsgAlloc(OS_MEM_DEFAULT_LCDYN_PT,10,8);
    ICUNIT_ASSERT_NOT_EQUAL(uwRet1, OS_MSG_CREATE_ERR, uwRet1);

    uwRet = SRE_SwiCreate(&uwSwiID, &stSwiPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    SRE_HuntByName(SRE_GetCoreID(),"MsgSwi_903", &uwSwiPID);
    ICUNIT_ASSERT_NOT_EQUAL(uwSwiPID, OS_ERRNO_HUNT_THREAD_NOT_CREAT, uwSwiPID);

    g_puwTaskPID = 0;
    SRE_TaskSelf(&g_puwTaskPID);

    uwRet = __SRE_MsgSend((VOID*)uwRet1, OS_MSG_PAYLOAD, uwSwiPID, OS_MSG_URGENT);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_uniMsgReceiveInSWI_001
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ����ղ��ԣ����жϴ�������Ϣ�����ж��ﴦ�����������Ϣ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgReceiveInSWI_001_Func()
{
    UINT32      uwMsgHdl;
    UINT32      uwMsgID;
    MSG_PID_T   uwSenderPID;

    uwMsgHdl = TS_SRE_MsgRecv(0xfffffffE,&uwMsgID,&uwSenderPID);
    ICUNIT_ASSERT_NOT_EQUAL(uwMsgHdl, OS_MSG_RECEIVE_ERR, uwMsgHdl);

    return SRE_OK;
}

OS_SEC_TEXT3_UT UINT32 UT_uniMsgReceiveInSWI_001()
{
    UINT32          uwRet;
    SWI_HANDLE_T    uwSwiID;

    SWI_INIT_PARA_S stSwiPara;

    stSwiPara.pcSwiName = "MsgSwi_904";
    stSwiPara.pfnHandler = (SWI_PROC_FUNC)UT_uniMsgReceiveInSWI_001_Func;
    stSwiPara.usPriority = 15;
    stSwiPara.uwInitValue = 0xffffffff;

    uwRet = SRE_SwiCreate(&uwSwiID, &stSwiPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}


/**
*-@test  UT_uniMsgQSend_001
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ�鷢�ͽ��ղ��ԣ������߳�PID�Ƿ�������ʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgQSend_001(void)
{
    UINT32          uwRet;
    UINT32          uwTskHdl;
    UINT32 auwMsg[3];

    SRE_HuntByName(SRE_GetCoreID(),"TestTask", &uwTskHdl);
    ICUNIT_ASSERT_EQUAL((uwTskHdl & 0xffff0000), 0, uwTskHdl);

    uwRet = __SRE_MsgSend(auwMsg , 0, uwTskHdl + 0xffff, 0);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_PID_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_uniMsgQSend_002
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ�鷢�ͽ��ղ��ԣ������߳�QID�Ƿ�������ʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgQSend_002(void)
{
    UINT32          uwRet;
    UINT32          uwTskHdl;
    UINT32          auwMsg[3];

    SRE_HuntByName(SRE_GetCoreID(),"TestTask", &uwTskHdl);
    ICUNIT_ASSERT_EQUAL((uwTskHdl & 0xffff0000), 0, uwTskHdl);

    uwRet = __SRE_MsgSend((VOID*)auwMsg,0, uwTskHdl , 10);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_uniMsgQSend_003
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ�鷢�ͽ��ղ��ԣ������߳�QID�Ƿ� > 15������ʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgQSend_003(void)
{
    UINT32          uwRet;
    UINT32          uwTskHdl;
    UINT32 auwMsg[3];

    SRE_HuntByName(SRE_GetCoreID(),"TestTask", &uwTskHdl);
    ICUNIT_ASSERT_EQUAL((uwTskHdl & 0xffff0000), 0, uwTskHdl);


    uwRet = __SRE_MsgSend(auwMsg,0, uwTskHdl , 16);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet);

    return SRE_OK;
}


/**
*-@test  UT_uniMsgQRecv_001
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ�鷢�ͽ��ղ��ԣ������߳�Ϊ���жϣ�����ʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/

OS_SEC_TEXT3_UT VOID Hook_Swi_MsgQRecv(UINT32 uwArg)
{
    UINT32 uwRet;
    uwRet = SRE_MsgQRecv(NULL, NULL, NULL , 0, OS_WAIT_FOREVER);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_MSG_QUEUE_EMPTY, uwRet);

}

OS_SEC_TEXT3_UT UINT32 UT_uniMsgQRecv_001()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    SWI_INIT_PARA_S stSwiPara;

    stSwiPara.pcSwiName = "Swi_12";
    stSwiPara.pfnHandler = (SWI_PROC_FUNC)Hook_Swi_MsgQRecv;
    stSwiPara.usPriority = 12;
    stSwiPara.uwInitValue = 0xff;

    uwRet = SRE_SwiCreate(&uwSwiID, &stSwiPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);

EXIT:
    if (0xff != uwSwiID) (void)SRE_SwiDelete(uwSwiID);
    return SRE_OK;
}


/**
*-@test  UT_uniMsgQRecv_002
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ�鷢�ͽ��ղ��ԣ������߳�ΪӲ�жϣ�����ʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
extern VOID UT_HwiTrigger(UINT32 uwIntNum);
OS_SEC_TEXT3_UT VOID Hook_Hwi_MsgQRecv(UINT32 uwArg)
{
    UINT32 uwRet;
    uwRet = SRE_MsgQRecv(NULL, NULL, NULL , 0, OS_WAIT_FOREVER);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_MSG_THREAD_INVALID, uwRet);

}

OS_SEC_TEXT3_UT UINT32 UT_uniMsgQRecv_002()
{
    UINT32 uwRet;

    uwRet = SRE_HwiSetAttr(7, UT_HWI_PRIO_0, OS_HWI_MODE_COMBINE);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_HwiCreate(7, (HWI_PROC_FUNC)Hook_Hwi_MsgQRecv,7);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)SRE_HwiEnable(7);

    UT_HwiTrigger(7);

    (VOID)SRE_HwiDisable(7);

    SRE_HwiDelete(7);
    return SRE_OK;
}

/**
*-@test  UT_uniMsgQRecv_002
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��Ϣģ�鷢�ͽ��ղ��ԣ������߳�QID�Ƿ�������ʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgQRecv_003()
{
    UINT32 uwRet;
    uwRet = SRE_MsgQRecv(NULL, NULL, NULL , 12, OS_WAIT_FOREVER);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MSG_QID_INVALID, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_uniMsgQNumGet_001
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��ȡָ������ָ�����е���Ϣ����IDLE���񣬻�ȡʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgQNumGet_001()
{
    UINT32 uwRet;
    uwRet = SRE_MsgQNumGet(g_uwIdleTaskID ,0 );
    ICUNIT_ASSERT_EQUAL(uwRet, OS_MSGQ_NUM_GET_ERR, uwRet);
    return SRE_OK;
}


/**
*-@test  UT_uniMsgQNumGet_002
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��ȡָ������ָ�����е���Ϣ�������жϣ���ȡʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgQNumGet_002()
{
    UINT32 uwRet;
    uwRet = SRE_MsgQNumGet(g_usSwiMaxNum - 1 ,0 );
    ICUNIT_ASSERT_EQUAL(uwRet, OS_MSGQ_NUM_GET_ERR, uwRet);
    return SRE_OK;
}

/**
*-@test  UT_uniMsgSend_003
*-@tspec  ��Ϣģ��UT����
*-@ttitle  ��ȡ��Ϣ�����ϵ���Ϣ����--��������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_uniMsgQNumGet_003()
{
    UINT32 uwRet;
    UINT32 uwPid;
    uwRet = SRE_TaskSelf(&uwPid);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_MsgQNumGet(uwPid ,0 );
    ICUNIT_ASSERT_NOT_EQUAL(uwRet, OS_MSGQ_NUM_GET_ERR, uwRet);
    return SRE_OK;

}
#endif

/* ��ڲ�����  */
OS_SEC_TEXT3_UT void UT_sre_msg(void)
{
    iUINT32 uiSuiteId;

    //uniMsgTest();
    //uniMsgTest1();
    //UT_uniMsg_PtCreate();

    TEST_ADD_SUITE(uiSuiteId, "UT_sre_msg");

#if(YES == OS_INCLUDE_MSG)
    //TEST_ADD_CASE(UT_SRE_MsgSend_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgSend_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgSend_003, uiSuiteId, Label_RUN)
    //TEST_ADD_CASE(UT_SRE_MsgSend_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_MsgSend_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgSend_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgSend_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgSend_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgSend_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgSend_010, uiSuiteId, Label_RUN);

    //TEST_ADD_CASE(UT_SRE_MsgQSend_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_MsgQSend_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_MsgQSend_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_010, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_011, uiSuiteId, Label_RUN);
    #if(OS_MEM_ALGORITHM_MCPOOL == YES)
    TEST_ADD_CASE(UT_SRE_MsgQSend_012, uiSuiteId, Label_RUN);
    #endif
    TEST_ADD_CASE(UT_SRE_MsgQSend_013, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_014, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_015, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_016, uiSuiteId, Label_RUN);
    #if 1
    TEST_ADD_CASE(UT_SRE_MsgQSend_017, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_018, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgQSend_019, uiSuiteId, Label_RUN);
    #endif
#if 0
    TEST_ADD_CASE(UT_SRE_MsgReceive_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgReceive_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgReceive_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgReceive_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgReceive_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MsgReceive_006, uiSuiteId, Label_RUN);


    TEST_ADD_CASE(UT_uniMsgQRecv_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniMsgQRecv_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniMsgQRecv_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniMsgQNumGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniMsgQNumGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniMsgQNumGet_003, uiSuiteId, Label_RUN);
#endif
Label_RUN:
#endif

    TEST_RUN_SUITE(uiSuiteId);

    //UT_uniMsg_PtDelete();

}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
