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

extern UINT32 g_uwMaxMsgNum;           /* 用户配置的最大核内消息节点数 */

TSK_HANDLE_T uwTestTskHdl;
//补充用例需要用的的变量
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
*-@tspec  申请消息体内存接口测试
*-@ttitle  错误入参申请消息体内存
*-@tprecon
*-@tbrief
1.输入的分区号参数大于等于配置的最大支持分区号
*-@texpect
1.申请失败，记录错误码，并返回0
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
*-@tspec  申请消息体内存接口测试
*-@ttitle  错误入参申请消息体内存
*-@tprecon
*-@tbrief
1.输入的消息体内存大小参数为零，
*-@texpect
1.申请失败，记录错误码，并返回0值
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
*-@tspec  申请消息体内存接口测试
*-@ttitle  错误入参申请消息体内存
*-@tprecon
*-@tbrief
1.输入的消息体内存大小过大，如0x10000000,远超分区创建时的内存，
*-@texpect
1.申请失败，记录错误码，并返回0值
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
*-@tspec  申请消息体内存接口测试
*-@ttitle  错误入参申请消息体内存
*-@tprecon
*-@tbrief
1.输入的消息体内存地址对齐值大于8
*-@texpect
1.申请失败，记录错误码，并返回0值
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
*-@tspec  申请消息体内存接口测试
*-@ttitle  错误入参申请消息体内存
*-@tprecon
*-@tbrief
1.消息体内存大小不大于8字节，重复申请直至将所有消息结点用光
*-@texpect
1.申请失败，返回0值
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
*-@tspec  申请消息体内存接口测试
*-@ttitle  正确入参申请消息体内存
*-@tprecon
*-@tbrief
1.输入合理的分区号，合适的内存大小，对齐参数在[0,8]范围内
*-@texpect
1.消息体内存申请成功，返回消息体内存句柄
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
*-@tspec  申请消息体内存接口测试
*-@ttitle  正确入参申请消息体内存，地址对齐测试
*-@tprecon
*-@tbrief
1.输入合理的分区号，消息体句柄地址对齐为128字节，填充数据，该地址整除128
*-@texpect
1.消息体内存申请成功，地址整除128字节成功
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
*-@tspec  申请消息体内存接口测试
*-@ttitle  错误入参申请消息体内存
*-@tprecon
*-@tbrief
1.输入合理的分区号，输入SIZE参数为0xFFFFFFFF
*-@texpect
1.申请内存失败
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
*-@tspec  释放消息体内存接口测试
*-@ttitle  错误入参释放消息体内存
*-@tprecon
*-@tbrief
1.输入的消息体句柄为空，
*-@texpect
1.则返回错误码OS_ERRNO_MSG_HANDLE_INVALID
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
*-@tspec  释放消息体内存接口测试
*-@ttitle  错误入参释放消息体内存
*-@tprecon
*-@tbrief
1.输入的消息体句柄非32字节对齐
*-@texpect
1.则返回错误码OS_ERRNO_MSG_HANDLE_ADDR_UNALIGN
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
*-@tspec  释放消息体内存接口测试
*-@ttitle  错误入参释放消息体内存
*-@tprecon
*-@tbrief
1.输入的消息体句柄值不为空，且32字节对齐，但并非申请消息体内存返回的句柄值
*-@texpect
1.则返回错误码OS_ERRNO_MSG_HANDLE_INVALID
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
*-@tspec  释放消息体内存接口测试
*-@ttitle  错误入参释放消息体内存
*-@tprecon
*-@tbrief
1.重复释放长消息体内存
*-@texpect
1.则返回错误码OS_ERRNO_MSG_HANDLE_INVALID
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
*-@tspec  释放消息体内存接口测试
*-@ttitle  错误入参释放消息体内存
*-@tprecon
*-@tbrief
1.重复释放长消息体内存
*-@texpect
1.则返回错误码OS_ERRNO_MSG_HANDLE_INVALID
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
*-@tspec  释放消息体内存接口测试
*-@ttitle  长消息体内存未被接收处理，直接删除
*-@tprecon
*-@tbrief
1.创建一个低优先级任务
2.获取该任务PID
3.在测试任务中发送一个长消息给低优先级任务
4.删除该消息体
5.将测试任务挂起
6.低先级任务接收到测试任务发送的消息体
7.在测试任务中删除该消息
*-@texpect
1.创建一个低优先级任务成功
2.获取该任务PID成功
3.在测试任务中发送一个带消息体的消息给低优先级任务成功
4.删除该消息体失败，返回错误码OS_ERRNO_MSG_LMSG_IN_USE
5.将测试任务挂起成功
6.低先级任务接收到测试任务发送的消息体成功
7.在测试任务中删除该消息成功
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
*-@tspec  释放消息体内存接口测试
*-@ttitle  短消息体内存未被接收处理，直接删除
*-@tprecon
*-@tbrief
1.创建一个低优先级任务
2.获取该任务PID
3.在测试任务中发送一个短消息给低优先级任务
4.删除该消息体
5.将测试任务挂起
6.低先级任务接收到测试任务发送的短消息
7.在测试任务中删除该消息
*-@texpect
1.创建一个低优先级任务成功
2.获取该任务PID成功
3.在测试任务中发送一个短消息给低优先级任务成功
4.删除该消息体失败，返回错误码OS_ERRNO_MSG_SMSG_IN_USE
5.将测试任务挂起成功
6.低先级任务接收到测试任务发送的短消息成功
7.在测试任务中删除该消息成功
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
*-@tspec  释放消息体内存接口测试
*-@ttitle 正确入参释放消息体内存
*-@tprecon
*-@tbrief
1.确认该消息已经接收处理完毕后，输入的消息体句柄值为对应申请的消息体内存返回值
*-@texpect
1.消息体内存释放成功
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
*-@tspec  释放消息体内存接口测试
*-@ttitle 错误入参释放消息体内存
*-@tprecon
*-@tbrief
1.输入句柄值为1
*-@texpect
1.删除失败，返回错误码
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
*-@tspec  释放消息体内存接口测试
*-@ttitle 错误入参释放消息体内存
*-@tprecon
*-@tbrief
1.输入句柄值为0x4
*-@texpect
1.删除失败，返回错误码
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
*-@tspec  释放消息体内存接口测试
*-@ttitle 错误入参释放消息体内存
*-@tprecon
*-@tbrief
1.输入句柄值为0x50
*-@texpect
1.删除失败，返回错误码
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
 * 增加mccom模块的测试用例
 * 增加初始化打桩用例
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
 * 增加msg模块的测试用例
 * 发送核间短消息    并且让接收任务挂起
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
/* 入口测试套  */
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

   //////补充用例
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