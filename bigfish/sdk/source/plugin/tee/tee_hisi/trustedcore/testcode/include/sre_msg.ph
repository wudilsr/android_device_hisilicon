/**
* @file sre_msg.ph
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：消息模块的内部头文件。 \n
*/

#ifndef _SRE_MSG_PH
#define _SRE_MSG_PH

#include "sre_base.h"
#include "sre_msg.h"
#include "sre_list.ph"
#include "sre_sys.h"
#include "sre_sys.ph"
#include "sre_task.ph"
#include "sre_swi.ph"
#include "sre_mem.ph"
#include "sre_err.ph"

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
#include "sre_msgm.ph"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_msg
 * 使用于发送消息接口，表示附加消息体的消息。
 */
#define OS_MSG_LMSG         0

/**
 * @ingroup SRE_msg
 * 使用于发送消息接口，表示短消息。
 */
#define OS_MSG_SMSG         1

/**
 * @ingroup SRE_msg
 * 使用于发送消息接口，表示无附加消息体的消息。
 */
#define OS_MSG_NPLD         2

/* 将消息类型从驱动底层转换为上层,或者从上层转换为驱动层 */
#define OS_MSG_TYPE_L2H(uwPhyMsgType)    (uwPhyMsgType)
#define OS_MSG_TYPE_H2L(uwPhyMsgType)    (uwPhyMsgType)

#define OS_MSG_MAGIC_ALLOC          0xabc1                  /* 长消息体中消息头的魔术字状态，表示已申请可使用状态、可删除 */
#define OS_MSG_MAGIC_SEND           0xabc2                  /* 长消息体中消息头的魔术字状态，正在发送，不可删除 */
#define OS_MSG_MAGIC_IPCIRQ         0xabc4                  /* 长消息体中消息头的魔术字状态，正在核间处理状态，不可删除 */
#define OS_MSG_MAGIC_INLIST         0xabc8                  /* 长消息体中消息头的魔术字状态，正在接收，不可删除 */

#define OS_MSG_IN_USE               0x74                    /* 短消息处于发送，核间处理或者正在接收状态，不可删除 */
#define OS_MSG_RELEASABLE           0x78                    /* 短消息处于申请可使用或者接收完成状态，可删除 */
#define OS_MSG_DELETED              0x7c                    /* 短消息处于空闲状态，不可删除 */

#define OS_MSG_HEAD_LEN            sizeof(MSG_HEAD_S)          /* 消息体中消息头长度     */

#define OS_MSG_TSK_SCHE_REQ        0x01                        /* 消息发送返回值,任务            */
#define OS_MSG_SWI_ACTV_REQ        0x02
#define OS_MSG_TSK_NO_SCHE_REQ     0x03

/*核间消息发送时第一个word高4位0xf表示有消息体，0xa表示无消息体*/
#define OS_MSG_TYPE_PAYLOAD             ((UINT32)0xf)
#define OS_MSG_TYPE_NO_PAYLOAD          ((UINT32)0xa)


/* 消息头未使用过或使用过已经释放，用于计算消息头使用过程最大占用量
   消息空闲时存储在stList.pstPrev字段。 */
#define OS_MSG_NODE_UNUSED         0xFFFFFFFF
#define OS_MSG_NODE_USED           0xFFFF0000

#define OS_MSG_MAX_QID             7        /*任务的最大的消息队列ID*/

/*短消息Payload长度，不同平台有差异，该宏定义不对用户感知*/
#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
#define OS_SMSG_MAX_LEN                 8      /* SD6182：MSGM的第4个WORD为控制头，第3个WORD为MsgID，剩下2个WORD为短消息Payload */
#else
#define OS_SMSG_MAX_LEN                 0
#endif

#define OS_SMSG_MAGIC                 0x5A5A5A5A       /*短消息魔术字*/

#define OS_IS_SMSG(uwMsgHdl)          (OS_SMSG_MAGIC == *(UINT32 *)((uwMsgHdl) - sizeof(UINT32)))
#define OS_IS_LMSG(uwMsgHdl)          (OS_SMSG_MAGIC != *(UINT32 *)((uwMsgHdl) - sizeof(UINT32)))
#define OS_IS_NPLD(uwMsgHdl)          (!(uwMsgHdl))

#define OS_SMSG_HDL2NODE(uwMsgHdl)    (LIST_COMPONENT((uwMsgHdl), MSG_NODE_S, auwData[1]))
#define OS_SMSG_NODE2HDL(pstMsgNode)  (MSG_HANDLE_T)&(pstMsgNode->auwData[1])

#define MSG_PUBLIC_HEAD               \
    LIST_OBJECT_S stList;       /* 用于挂在进程消息接收队列，必须放在头位   */ \
    MSG_PID_T uwDstPid;         /* 消息接收者的pid                          */ \
    MSG_PID_T uwSrcPid;         /* 消息发送者的pid                      */     \
    UINT32 uwMsgID;             /* 4字节的消息数据  */                         \
    UINT8  ucQID;               /* 接收任务的QID                            */ \
    UINT8  ucMsgType;           /* 消息类型：无消息体，长消息，短消息       */

typedef struct tagMsgPubHead
{
    MSG_PUBLIC_HEAD
}MSG_PUB_HEAD_S;

typedef struct tagMsgHead
{
    MSG_PUBLIC_HEAD
    UINT8  bShared;             /* 消息内存是否共享                         */
    UINT8  bCachable;           /* 消息内存是否即共享又Cache            */
    UINT16 usLength;            /* 发送的消息体内存长度                     */
    UINT16 usMagicWord;         /* 魔术字                                   */
    VOID   *pMemBlock ;         /* 消息头相对内存块起始地址的偏移       */
} MSG_HEAD_S;

typedef struct tagMsgNode
{
    MSG_PUBLIC_HEAD
    UINT8  ucSmsgLen;           /* 短消息长度 */
    UINT8  ucReleasable;        /* 可释放标志 */
    UINT32 auwData[1 + (OS_SMSG_MAX_LEN/sizeof(UINT32))];  /*数组的第0个WORD存放短消息魔术字，后面的WORD才用于存储短消息的净荷*/
} MSG_NODE_S;

extern  MSG_NODE_S       *g_pstFreeLcMsgHead;      /* 指向第一个核内消息空闲节点   */

/* 核间消息发送钩子函数   */
typedef UINT32 (* MCMSG_SEND_FUNC)(MSG_HANDLE_T uwMsgHandle, UINT32 uwMsgID, MSG_PID_T  uwDstPID, MSG_PID_T uwSrcPID, UINT8 ucQid);

/* 核间消息发送接口       */
#define OS_MSG_CROSS_SEND(uwMsgHandle, uwMsgID, uwDstPID, uwSrcPid, ucQid) \
    ((g_pfnMsgSend == NULL)?OS_ERRNO_MCMSG_HOOK_NULL:g_pfnMsgSend(uwMsgHandle, uwMsgID, uwDstPID, uwSrcPid, ucQid))

EXTERN_FAR TSK_CB_S *g_pRunningTask;                                              /* 指向当前运行的任务控制块 */
extern UINT8 osMsgSubmit(MSG_HANDLE_T uwMsgHandle,
                         UINT32 uwThreadID,
                         UINT8  ucQid,
                         UINT8  ucMsgType);
extern UINT32 osMsgDstIDCheck(MSG_NODE_S *pstMsgNode, UINT32 uwType);

/* 关中断保护由调用者保证!!! */
OS_SEC_ALW_INLINE INLINE MSG_NODE_S* osMsgNodeAlloc(UINT8 ucMsgLen, UINT8 ucReleasable)
{
    MSG_NODE_S *pstMsgNode = g_pstFreeLcMsgHead;

    if (NULL != pstMsgNode)
    {
        g_pstFreeLcMsgHead = (MSG_NODE_S *)pstMsgNode->uwMsgID; /*空闲链表头指向下一个节点*/
        pstMsgNode->ucReleasable = ucReleasable;
        pstMsgNode->ucSmsgLen    = ucMsgLen;
    }
    return pstMsgNode;
}

/* 关中断保护和指针的有效性由调用者保证!!! */
OS_SEC_ALW_INLINE INLINE VOID osMsgNodeFree(MSG_NODE_S* pstMsgNode)
{
    pstMsgNode->stList.pstPrev = (LIST_OBJECT_S *)OS_MSG_NODE_USED;
    pstMsgNode->ucReleasable   = OS_MSG_DELETED;  /*不允许重复释放*/
    pstMsgNode->ucSmsgLen      = 0;
    pstMsgNode->uwMsgID = (UINT32)g_pstFreeLcMsgHead;/*将消息结点插入到空闲链表表头*/
    g_pstFreeLcMsgHead  = pstMsgNode;/*空闲链表移至表头*/

    return;
}

/* 消息中断，读取消息队列任务，并转发至对应进程 */
#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170))
OS_SEC_ALW_INLINE INLINE VOID osMsgIrptHandler(UINT32 uwPara, UINT32 uwPara2)
{
    UINT8       ucShedReq;
    MSG_HEAD_S *pstMsgHead;
    MSG_NODE_S *pstMsgNode;
    UINT32      uwRetErr;
    UINT32      uwDstPid;
    UINT32      uwIntSave; /* 开关中断 */

    uwIntSave = SRE_IntLock();
    if(OS_MSG_TYPE_NO_PAYLOAD == ((uwPara & 0xf0000000) >> 28))//高4位为0xa，表示无消息体
    {
        if (NULL == (pstMsgNode = g_pstFreeLcMsgHead))
        {
            uwRetErr = OS_ERRNO_MSG_NO_MSGNODE;
            OS_REPORT_ERROR(uwRetErr);
            (VOID)SRE_IntRestore(uwIntSave);
            return;
        }
        g_pstFreeLcMsgHead = (MSG_NODE_S *)pstMsgNode->uwMsgID;

        /* 创建节点信息 */
        pstMsgNode->uwDstPid = COMPOSE_PID(SRE_GetCoreID(), (uwPara & 0xff)); //by zhangweiwei,有无消息体时的信息保持一致
        pstMsgNode->uwSrcPid = (uwPara  & 0xffff00) >> 8;
        pstMsgNode->ucQID    = (uwPara  & 0xf000000) >> 24;
        pstMsgNode->uwMsgID  = uwPara2;
        if(osMsgDstIDCheck(pstMsgNode, OS_MSG_NPLD))
        {
            (VOID)SRE_IntRestore(uwIntSave);
            return;
        }
        uwDstPid = uwPara & 0xff;

        ucShedReq = osMsgSubmit((UINT32)pstMsgNode, uwDstPid, pstMsgNode->ucQID, OS_MSG_NPLD);
    }
    else
    {
        pstMsgHead = (MSG_HEAD_S *)uwPara2;

        /*DTS2010100902412  增加目的线程有效性检测，释放资源 by00144072*/
        if(osMsgDstIDCheck((MSG_NODE_S *)pstMsgHead, OS_MSG_LMSG))
        {
            (VOID)SRE_IntRestore(uwIntSave);
            return;
        }
        pstMsgHead->usMagicWord = OS_MSG_MAGIC_IPCIRQ;

        uwDstPid = pstMsgHead->uwDstPid;
        ucShedReq = osMsgSubmit((UINT32)pstMsgHead, GET_HANDLE(pstMsgHead->uwDstPid), pstMsgHead->ucQID, OS_MSG_LMSG);
    }

    (VOID)SRE_IntRestore(uwIntSave);

    if (OS_MSG_TSK_SCHE_REQ == ucShedReq)
    {
        osTskScheduleFast();
    }
    else if (OS_MSG_SWI_ACTV_REQ == ucShedReq)
    {
        osSwiIrptHandler(GET_HANDLE(uwDstPid), (UINT32)MCCOM_SWI_ACT);
    }
}

#elif ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
OS_SEC_ALW_INLINE INLINE VOID osMsgIrptHandler(UINT32 auwQData[4])
{
    UINT8       ucShedReq;
    MSG_HEAD_S *pstMsgHead;
    MSG_NODE_S *pstMsgNode;
    UINT32      uwDstIdx;
    UINT32      uwIntSave;
    UINT32      uwHead;
    UINT32      uwMsgType;
    UINT8       ucSmsgLen;

    uwHead    = auwQData[3];
    uwMsgType = OS_MSG_TYPE_L2H(OS_QDATA_HEAD_TYPE(uwHead));
    uwDstIdx  = OS_QDATA_HEAD_DESTID(uwHead);

    uwIntSave = SRE_IntLock();

    if (uwMsgType != OS_MSG_LMSG)
    {
        ucSmsgLen = OS_QDATA_HEAD_SMSGLEN(uwHead);
        if (NULL == (pstMsgNode = osMsgNodeAlloc(ucSmsgLen, OS_MSG_IN_USE)))
        {
            OS_REPORT_ERROR(OS_ERRNO_MSG_NO_MSGNODE);
            (VOID)SRE_IntRestore(uwIntSave);
            return;
        }

        pstMsgNode->stList.pstPrev = NULL;

        pstMsgNode->uwDstPid  = COMPOSE_PID(SRE_GetCoreID(), uwDstIdx);
        pstMsgNode->uwSrcPid  = OS_QDATA_HEAD_SRCPID(uwHead);
        pstMsgNode->ucQID     = OS_QDATA_HEAD_QUE(uwHead);
        pstMsgNode->uwMsgID   = auwQData[2];
        pstMsgNode->auwData[1] = auwQData[0];
        pstMsgNode->auwData[2] = auwQData[1];   // 出于代码归一的考虑，无消息体消息，同样拷贝auwQData[0]和auwQData[1]

        /*无消息和短消息的校验统一判断*/
        if(osMsgDstIDCheck( pstMsgNode, uwMsgType ))
        {
            (VOID)SRE_IntRestore(uwIntSave);
            return;
        }
        ucShedReq = osMsgSubmit((UINT32)pstMsgNode, uwDstIdx, pstMsgNode->ucQID, uwMsgType);
    }
    else
    {
        pstMsgHead = (MSG_HEAD_S *)auwQData[0];

        if(osMsgDstIDCheck((MSG_NODE_S *)pstMsgHead, uwMsgType))
        {
            (VOID)SRE_IntRestore(uwIntSave);
            return;
        }
        pstMsgHead->usMagicWord = OS_MSG_MAGIC_IPCIRQ;
        ucShedReq = osMsgSubmit((UINT32)pstMsgHead, uwDstIdx, pstMsgHead->ucQID, uwMsgType);
    }

    (VOID)SRE_IntRestore(uwIntSave);

    if (OS_MSG_TSK_SCHE_REQ == ucShedReq)
    {
        osTskScheduleFast();
    }
    else if (OS_MSG_SWI_ACTV_REQ == ucShedReq)
    {
        osSwiIrptHandler(uwDstIdx, (UINT32)MCCOM_SWI_ACT);
    }
}
#endif //(OS_HARDWARE_PLATFORM == OS_XTENSA2)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_MSG_PH */

/**
 * History:
 * 2008-09-30 z00134877: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */


