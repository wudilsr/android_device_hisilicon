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
//extern UINT8 m_aucMemRegion02[UT_MEM_DYNAMIC_PT_SIZE] ;   /* 私有动态Page内存分区(缺省)   */
//extern UINT8 m_aucMemRegion03[UT_MEM_MCDYNAMIC_PT_SIZE] ;   /* 共享动态Pool内存分区(缺省)   */

#define UT_HWI_EVENT_C_1 7

extern UINT8 osMsgSubmit(MSG_HANDLE_T uwMsgHandle,UINT32 uwThreadID,UINT8 ucPrio,UINT8 ucQid);

extern UINT32 osMcComEnQ(UINT32 uwDstPid, UINT8  ucOprtType, UINT32 uwOprtNum);

#define ASSERT_CONDITION(b)  (b)

/******************************************************打桩函数******************************************************/
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
        /* 增加可cache属性配置 */
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

    /*接收第一条消息*/
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

    /*接收第二条消息*/
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入非法入参
*-@tprecon
*-@tbrief
1.指定线程发送消息，输入的uwMsgHandle为OS_MSG_NO_PAYLOAD，无效的目的线程入参
*-@texpect
1.消息发送失败，返回错误码OS_ERRNO_MSG_PID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入非法入参
*-@tprecon
*-@tbrief
1.目的任务创建时消息队列个数为零
2.输入的uwMsgHandle为OS_MSG_NO_PAYLOAD，目的线程的PID入参由SRE_HuntByName接口获得
*-@texpect
1.目的任务创建成功
1.发送消息失败，返回错误码OS_ERRNO_MSG_QID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入合法参数
*-@tprecon
*-@tbrief
1.创建一个低优先级任务
2.获取该任务PID
3.在测试任务中发送一个不带消息的消息给低优先级任务
4.将测试任务挂起
5.低先级任务接收到测试任务发送的消息体
*-@texpect
1.创建一个低优先级任务成功
2.获取该任务PID成功
3.在测试任务中发送一个不带消息体消息给低优先级任务成功
4.将测试任务挂起成功
5.低先级任务接收到测试任务发送的消息体成功
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.申请长消息体句柄
2.输入的uwMsgHandle为申请消息体返回的句柄，无效的目的线程入参
*-@texpect
1.申请消息体句柄成功
2.消息发送失败，返回错误码OS_ERRNO_MSG_PID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.申请短消息体句柄
2.输入的uwMsgHandle为申请消息体返回的句柄，无效的目的线程入参
*-@texpect
1.申请消息体句柄成功
2.消息发送失败，返回错误码OS_ERRNO_MSG_PID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入非法入参
*-@tprecon
*-@tbrief
1.目的任务创建时消息队列个数为零
2.申请短消息体句柄
3.目的线程的PID入参由SRE_HuntByName接口获得
*-@texpect
1.目的任务创建成功
2.申请短消息体句柄成功
3.发送消息失败，返回错误码OS_ERRNO_MSG_QID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入非法入参
*-@tprecon
*-@tbrief
1.目的任务创建时消息队列个数为零
2.申请长消息体句柄
3.目的线程的PID入参由SRE_HuntByName接口获得
*-@texpect
1.目的任务创建成功
2.申请长消息体句柄成功
3.发送消息失败，返回错误码OS_ERRNO_MSG_QID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入非法入参
*-@tprecon
*-@tbrief
1.输入的消息体句柄uwMsgHandle不为OS_MSG_NO_PAYLOAD，也不是申请消息体内存返回的句柄值，
2.创建任务时，输入的消息队列个数大于零
3.目的线程的PID入参由SRE_HuntByName接口获得
*-@texpect
1.申请内存成功
2.创建任务成功
3.消息发送失败，返回错误码OS_ERRNO_MSG_HANDLE_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入合法参数
*-@tprecon
*-@tbrief
1.创建一个低优先级任务
2.获取该任务PID
3.在测试任务中发送一个短消息给低优先级任务
4.将测试任务挂起
5.低先级任务接收到测试任务发送的消息体
*-@texpect
1.创建一个低优先级任务成功
2.获取该任务PID成功
3.在测试任务中发送一个短消息给低优先级任务成功
4.将测试任务挂起成功
5.低先级任务接收到测试任务发送的消息体成功
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程发送消息，输入合法参数
*-@tprecon
*-@tbrief
1.创建一个低优先级任务
2.获取该任务PID
3.在测试任务中发送一个长消息给低优先级任务
4.将测试任务挂起
5.低先级任务接收到测试任务发送的消息体
*-@texpect
1.创建一个低优先级任务成功
2.获取该任务PID成功
3.在测试任务中发送一个长消息给低优先级任务成功
4.将测试任务挂起成功
5.低先级任务接收到测试任务发送的消息体成功
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.输入的uwMsgHandle为OS_MSG_NO_PAYLOAD，无效的目的线程入参
*-@texpect
2.消息发送失败，返回错误码OS_ERRNO_MSG_PID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.创建任务时，消息队列个数为零
2.目的线程的PID由SRE_HuntByName接口获取
3.发送消息，输入的uwMsgHandle为OS_MSG_NO_PAYLOAD，输入有效的PID
*-@texpect
1.任务创建成功
2.目的线程的PID由SRE_HuntByName接口获取成功
3.发送消息失败，返回错误码OS_ERRNO_MSG_QID_INVALIDD
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.创建任务时，消息队列个数大于零
2.目的线程的PID由SRE_HuntByName接口获取
3.发送消息，输入的uwMsgHandle为OS_MSG_NO_PAYLOAD，输入有效的PID，输入的QID号大于等于任务创建时的队列个数
*-@texpect
1.任务创建成功
2.目的线程的PID由SRE_HuntByName接口获取成功
3.发送消息失败，返回错误码OS_ERRNO_MSG_QID_INVALIDD
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，输入合法参数
*-@tprecon
*-@tbrief
1.创建任务时，消息队列个数大于零
2.目的线程的PID由SRE_HuntByName接口获取
3.发送消息，输入的uwMsgHandle为OS_MSG_NO_PAYLOAD，输入有效的PID，输入的QID号小于任务创建时的队列个数
*-@texpect
1.任务创建成功
2.目的线程的PID由SRE_HuntByName接口获取成功
3.发送消息成功
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.申请短消息体句柄
2.输入的uwMsgHandle为申请消息体返回的句柄，无效的目的线程入参
*-@texpect
1.申请消息体句柄成功
2.消息发送失败，返回错误码OS_ERRNO_MSG_PID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.申请长消息体句柄
2.输入的uwMsgHandle为申请消息体返回的句柄，无效的目的线程入参
*-@texpect
1.申请消息体句柄成功
2.消息发送失败，返回错误码OS_ERRNO_MSG_PID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.目的任务创建时消息队列个数为零
2.申请短消息体句柄
3.目的线程的PID入参由SRE_HuntByName接口获得
*-@texpect
1.目的任务创建成功
2.申请短消息体句柄成功
3.发送消息失败，返回错误码OS_ERRNO_MSG_QID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，输入非法参数
*-@tprecon
*-@tbrief
1.目的任务创建时消息队列个数为零
2.申请长消息体句柄
3.目的线程的PID入参由SRE_HuntByName接口获得
*-@texpect
1.目的任务创建成功
2.申请长消息体句柄成功
3.发送消息失败，返回错误码OS_ERRNO_MSG_QID_INVALID
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，保序测试
*-@tprecon
*-@tbrief
1.创建一个高于测试任务优先级的任务，消息队列个数大于0
2.创建一个低于测试任务优先级的任务，消息队列个数大于0
3.测试任务向低优先级任务发送一个不带消息带的消息
4.切换到高优先级任务，在高优先级任务里再次向低优先级任务发送一个不带消息带的消息
5.先处理前一个消息
6.再处理后一个消息
*-@texpect
1.高优先级任务创建成功
2.低优先级任务创建成功
3.测试任务向低优先级任务发送消息成功
4.高优先级任务向低优先级任务发送消息成功
5.先处理前一个消息成功
6.再处理后一个消息成功
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，保序测试
*-@tprecon
*-@tbrief
1.创建一个高于测试任务优先级的任务，消息队列个数大于0
2.创建一个低于测试任务优先级的任务，消息队列个数大于0
3.通过私有动态内存申请消息体内存
4.测试任务向低优先级任务发送一个短消息
5.切换到高优先级任务，在高优先级任务里通过私有动态内存申请消息体内存
6.在高优先级任务里再次向低优先级任务发送一个短消息
7.先处理前一个消息
8.再处理后一个消息
*-@texpect
1.高优先级任务创建成功
2.低优先级任务创建成功
3.通过私有动态内存申请消息体内存成功
4.测试任务向低优先级任务发送消息成功
5.切换到高优先级任务，在高优先级任务里通过私有动态内存申请消息体内存成功
6.高优先级任务向低优先级任务发送消息成功
7.先处理前一个消息成功
8.再处理后一个消息成功
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，保序测试
*-@tprecon
*-@tbrief
1.创建一个高于测试任务优先级的任务，消息队列个数大于0
2.创建一个低于测试任务优先级的任务，消息队列个数大于0
3.通过私有动态内存申请消息体内存
4.测试任务向低优先级任务发送一个长消息
5.切换到高优先级任务，在高优先级任务里通过私有动态内存申请消息体内存
6.在高优先级任务里再次向低优先级任务发送一个长消息
7.先处理前一个消息
8.再处理后一个消息
*-@texpect
1.高优先级任务创建成功
2.低优先级任务创建成功
3.通过私有动态内存申请消息体内存成功
4.测试任务向低优先级任务发送消息成功
5.切换到高优先级任务，在高优先级任务里通过私有动态内存申请消息体内存成功
6.高优先级任务向低优先级任务发送消息成功
7.先处理前一个消息成功
8.再处理后一个消息成功
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的消息队列发送消息，保序测试
*-@tprecon
*-@tbrief
1.创建一个高于测试任务优先级的任务，消息队列个数大于0
2.创建一个低于测试任务优先级的任务，消息队列个数大于0
3.通过共享动态内存申请消息体内存
4.测试任务向低优先级任务发送一个长消息
5.切换到高优先级任务，在高优先级任务里通过共享动态内存申请消息体内存
6.在高优先级任务里再次向低优先级任务发送一个长消息
7.先处理前一个消息
8.再处理后一个消息
*-@texpect
1.高优先级任务创建成功
2.低优先级任务创建成功
3.通过私有动态内存申请消息体内存成功
4.测试任务向低优先级任务发送消息成功
5.切换到高优先级任务，在高优先级任务里通过共享动态内存申请消息体内存成功
6.高优先级任务向低优先级任务发送消息成功
7.先处理前一个消息成功
8.再处理后一个消息成功
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
*-@tspec  消息模块UT测试
*-@ttitle  指定线程的软中断发送消息，正确入参
*-@tprecon
*-@tbrief
1.创建的一个软中断
2.目的软中断的PID入参由SRE_HuntByName接口获取
3.输入的消息体句柄uwMsgHandle为OS_MSG_NO_PAYLOAD
*-@texpect
1.创建的一个软中断成功
2.目的软中断的PID入参由SRE_HuntByName接口获取成功
3.消息发送成功
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
*-@tspec  消息模块UT测试
*-@ttitle  在软中断向指定线程发送消息，正确入参
*-@tprecon
*-@tbrief
1.创建一个软中断
2.目的任务线程的PID入参由SRE_HuntByName接口获取
3.在软中断里，发送消息，输入的消息体句柄uwMsgHandle为OS_MSG_NO_PAYLOAD
4.在任务里以永久等待方式接收消息
*-@texpect
1.创建一个软中断成功
2.目的任务线程的PID入参由SRE_HuntByName接口获取成功
3.消息发送成功
4.在任务里以永久等待方式接收成功
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
*-@tspec  消息模块UT测试
*-@ttitle  在软中断向指定线程发送消息，正确入参
*-@tprecon
*-@tbrief
1.创建一个软中断
2.目的任务线程的PID入参由SRE_HuntByName接口获取
3.在软中断里，发送消息，输入的消息体句柄uwMsgHandle为申请短消息返回的句柄
4.在任务里以永久等待方式接收消息
*-@texpect
1.创建一个软中断成功
2.目的任务线程的PID入参由SRE_HuntByName接口获取成功
3.消息发送成功
4.在任务里以永久等待方式接收成功
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
*-@tspec  消息模块UT测试
*-@ttitle  在软中断向指定线程发送消息，正确入参
*-@tprecon
*-@tbrief
1.创建一个软中断
2.目的任务线程的PID入参由SRE_HuntByName接口获取
3.在软中断里，发送消息，输入的消息体句柄uwMsgHandle为申请长消息返回的句柄
4.在任务里以永久等待方式接收消息
*-@texpect
1.创建一个软中断成功
2.目的任务线程的PID入参由SRE_HuntByName接口获取成功
3.消息发送成功
4.在任务里以永久等待方式接收成功
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
*-@tspec  消息模块UT测试
*-@ttitle  硬中断向指定任务线程发送消息，正确入参
*-@tprecon
*-@tbrief
1.创建一个硬中断
2.目的任务线程的PID入参由SRE_HuntByName接口获取
3.使用并触发硬中断
4.输入的消息体句柄uwMsgHandle为OS_MSG_NO_PAYLOAD
5.任务里以永久等待方式接收消息
*-@texpect
1.创建一个硬中断成功
2.目的任务线程的PID入参由SRE_HuntByName接口获取成功
3.使用并触发硬中断成功
4.消息发送成功
5.任务里以永久等待方式接收消息成功
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
*-@tspec  消息模块UT测试
*-@ttitle  硬中断向指定任务线程发送消息，正确入参
*-@tprecon
*-@tbrief
1.创建一个硬中断
2.目的任务线程的PID入参由SRE_HuntByName接口获取
3.使用并触发硬中断
4.输入的消息体句柄uwMsgHandle为申请短消息返回的句柄
5.任务里以永久等待方式接收消息
*-@texpect
1.创建一个硬中断成功
2.目的任务线程的PID入参由SRE_HuntByName接口获取成功
3.使用并触发硬中断成功
4.消息发送成功
5.任务里以永久等待方式接收消息成功
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
*-@tspec  消息模块UT测试
*-@ttitle  硬中断向指定任务线程发送消息，正确入参
*-@tprecon
*-@tbrief
1.创建一个硬中断
2.目的任务线程的PID入参由SRE_HuntByName接口获取
3.使用并触发硬中断
4.输入的消息体句柄uwMsgHandle为申请长消息返回的句柄
5.任务里以永久等待方式接收消息
*-@texpect
1.创建一个硬中断成功
2.目的任务线程的PID入参由SRE_HuntByName接口获取成功
3.使用并触发硬中断成功
4.消息发送成功
5.任务里以永久等待方式接收消息成功
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
*-@tspec  消息模块UT测试
*-@ttitle  消息向一个软中断发送无消息体消息!
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块接收测试，系统状态g_vuwUniFlag为硬中断激活
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块接收测试，系统状态g_vuwUniFlag为软中断激活
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块接收测试，在软中断中接收消息
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块接收测试，在软中断中接收消息，紧急方式发送
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块接收测试，两次发送在软中断中接收消息，紧急方式发送
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块接收测试，软中断创建后消息，软中断里处理函数里接收消息
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块发送接收测试，接收线程PID非法，返回失败
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块发送接收测试，接收线程QID非法，返回失败
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块发送接收测试，接收线程QID非法 > 15，返回失败
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块发送接收测试，接收线程为软中断，返回失败
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块发送接收测试，接收线程为硬中断，返回失败
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
*-@tspec  消息模块UT测试
*-@ttitle  消息模块发送接收测试，接收线程QID非法，返回失败
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
*-@tspec  消息模块UT测试
*-@ttitle  获取指定进程指定队列的消息数。IDLE任务，获取失败
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
*-@tspec  消息模块UT测试
*-@ttitle  获取指定进程指定队列的消息数。软中断，获取失败
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
*-@tspec  消息模块UT测试
*-@ttitle  获取消息队列上的消息个数--正常场景
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

/* 入口测试套  */
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
