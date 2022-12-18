/**
* @file sre_msg.ph
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ��������Ϣģ����ڲ�ͷ�ļ��� \n
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
 * ʹ���ڷ�����Ϣ�ӿڣ���ʾ������Ϣ�����Ϣ��
 */
#define OS_MSG_LMSG         0

/**
 * @ingroup SRE_msg
 * ʹ���ڷ�����Ϣ�ӿڣ���ʾ����Ϣ��
 */
#define OS_MSG_SMSG         1

/**
 * @ingroup SRE_msg
 * ʹ���ڷ�����Ϣ�ӿڣ���ʾ�޸�����Ϣ�����Ϣ��
 */
#define OS_MSG_NPLD         2

/* ����Ϣ���ʹ������ײ�ת��Ϊ�ϲ�,���ߴ��ϲ�ת��Ϊ������ */
#define OS_MSG_TYPE_L2H(uwPhyMsgType)    (uwPhyMsgType)
#define OS_MSG_TYPE_H2L(uwPhyMsgType)    (uwPhyMsgType)

#define OS_MSG_MAGIC_ALLOC          0xabc1                  /* ����Ϣ������Ϣͷ��ħ����״̬����ʾ�������ʹ��״̬����ɾ�� */
#define OS_MSG_MAGIC_SEND           0xabc2                  /* ����Ϣ������Ϣͷ��ħ����״̬�����ڷ��ͣ�����ɾ�� */
#define OS_MSG_MAGIC_IPCIRQ         0xabc4                  /* ����Ϣ������Ϣͷ��ħ����״̬�����ں˼䴦��״̬������ɾ�� */
#define OS_MSG_MAGIC_INLIST         0xabc8                  /* ����Ϣ������Ϣͷ��ħ����״̬�����ڽ��գ�����ɾ�� */

#define OS_MSG_IN_USE               0x74                    /* ����Ϣ���ڷ��ͣ��˼䴦��������ڽ���״̬������ɾ�� */
#define OS_MSG_RELEASABLE           0x78                    /* ����Ϣ���������ʹ�û��߽������״̬����ɾ�� */
#define OS_MSG_DELETED              0x7c                    /* ����Ϣ���ڿ���״̬������ɾ�� */

#define OS_MSG_HEAD_LEN            sizeof(MSG_HEAD_S)          /* ��Ϣ������Ϣͷ����     */

#define OS_MSG_TSK_SCHE_REQ        0x01                        /* ��Ϣ���ͷ���ֵ,����            */
#define OS_MSG_SWI_ACTV_REQ        0x02
#define OS_MSG_TSK_NO_SCHE_REQ     0x03

/*�˼���Ϣ����ʱ��һ��word��4λ0xf��ʾ����Ϣ�壬0xa��ʾ����Ϣ��*/
#define OS_MSG_TYPE_PAYLOAD             ((UINT32)0xf)
#define OS_MSG_TYPE_NO_PAYLOAD          ((UINT32)0xa)


/* ��Ϣͷδʹ�ù���ʹ�ù��Ѿ��ͷţ����ڼ�����Ϣͷʹ�ù������ռ����
   ��Ϣ����ʱ�洢��stList.pstPrev�ֶΡ� */
#define OS_MSG_NODE_UNUSED         0xFFFFFFFF
#define OS_MSG_NODE_USED           0xFFFF0000

#define OS_MSG_MAX_QID             7        /*�����������Ϣ����ID*/

/*����ϢPayload���ȣ���ͬƽ̨�в��죬�ú궨�岻���û���֪*/
#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
#define OS_SMSG_MAX_LEN                 8      /* SD6182��MSGM�ĵ�4��WORDΪ����ͷ����3��WORDΪMsgID��ʣ��2��WORDΪ����ϢPayload */
#else
#define OS_SMSG_MAX_LEN                 0
#endif

#define OS_SMSG_MAGIC                 0x5A5A5A5A       /*����Ϣħ����*/

#define OS_IS_SMSG(uwMsgHdl)          (OS_SMSG_MAGIC == *(UINT32 *)((uwMsgHdl) - sizeof(UINT32)))
#define OS_IS_LMSG(uwMsgHdl)          (OS_SMSG_MAGIC != *(UINT32 *)((uwMsgHdl) - sizeof(UINT32)))
#define OS_IS_NPLD(uwMsgHdl)          (!(uwMsgHdl))

#define OS_SMSG_HDL2NODE(uwMsgHdl)    (LIST_COMPONENT((uwMsgHdl), MSG_NODE_S, auwData[1]))
#define OS_SMSG_NODE2HDL(pstMsgNode)  (MSG_HANDLE_T)&(pstMsgNode->auwData[1])

#define MSG_PUBLIC_HEAD               \
    LIST_OBJECT_S stList;       /* ���ڹ��ڽ�����Ϣ���ն��У��������ͷλ   */ \
    MSG_PID_T uwDstPid;         /* ��Ϣ�����ߵ�pid                          */ \
    MSG_PID_T uwSrcPid;         /* ��Ϣ�����ߵ�pid                      */     \
    UINT32 uwMsgID;             /* 4�ֽڵ���Ϣ����  */                         \
    UINT8  ucQID;               /* ���������QID                            */ \
    UINT8  ucMsgType;           /* ��Ϣ���ͣ�����Ϣ�壬����Ϣ������Ϣ       */

typedef struct tagMsgPubHead
{
    MSG_PUBLIC_HEAD
}MSG_PUB_HEAD_S;

typedef struct tagMsgHead
{
    MSG_PUBLIC_HEAD
    UINT8  bShared;             /* ��Ϣ�ڴ��Ƿ���                         */
    UINT8  bCachable;           /* ��Ϣ�ڴ��Ƿ񼴹�����Cache            */
    UINT16 usLength;            /* ���͵���Ϣ���ڴ泤��                     */
    UINT16 usMagicWord;         /* ħ����                                   */
    VOID   *pMemBlock ;         /* ��Ϣͷ����ڴ����ʼ��ַ��ƫ��       */
} MSG_HEAD_S;

typedef struct tagMsgNode
{
    MSG_PUBLIC_HEAD
    UINT8  ucSmsgLen;           /* ����Ϣ���� */
    UINT8  ucReleasable;        /* ���ͷű�־ */
    UINT32 auwData[1 + (OS_SMSG_MAX_LEN/sizeof(UINT32))];  /*����ĵ�0��WORD��Ŷ���Ϣħ���֣������WORD�����ڴ洢����Ϣ�ľ���*/
} MSG_NODE_S;

extern  MSG_NODE_S       *g_pstFreeLcMsgHead;      /* ָ���һ��������Ϣ���нڵ�   */

/* �˼���Ϣ���͹��Ӻ���   */
typedef UINT32 (* MCMSG_SEND_FUNC)(MSG_HANDLE_T uwMsgHandle, UINT32 uwMsgID, MSG_PID_T  uwDstPID, MSG_PID_T uwSrcPID, UINT8 ucQid);

/* �˼���Ϣ���ͽӿ�       */
#define OS_MSG_CROSS_SEND(uwMsgHandle, uwMsgID, uwDstPID, uwSrcPid, ucQid) \
    ((g_pfnMsgSend == NULL)?OS_ERRNO_MCMSG_HOOK_NULL:g_pfnMsgSend(uwMsgHandle, uwMsgID, uwDstPID, uwSrcPid, ucQid))

EXTERN_FAR TSK_CB_S *g_pRunningTask;                                              /* ָ��ǰ���е�������ƿ� */
extern UINT8 osMsgSubmit(MSG_HANDLE_T uwMsgHandle,
                         UINT32 uwThreadID,
                         UINT8  ucQid,
                         UINT8  ucMsgType);
extern UINT32 osMsgDstIDCheck(MSG_NODE_S *pstMsgNode, UINT32 uwType);

/* ���жϱ����ɵ����߱�֤!!! */
OS_SEC_ALW_INLINE INLINE MSG_NODE_S* osMsgNodeAlloc(UINT8 ucMsgLen, UINT8 ucReleasable)
{
    MSG_NODE_S *pstMsgNode = g_pstFreeLcMsgHead;

    if (NULL != pstMsgNode)
    {
        g_pstFreeLcMsgHead = (MSG_NODE_S *)pstMsgNode->uwMsgID; /*��������ͷָ����һ���ڵ�*/
        pstMsgNode->ucReleasable = ucReleasable;
        pstMsgNode->ucSmsgLen    = ucMsgLen;
    }
    return pstMsgNode;
}

/* ���жϱ�����ָ�����Ч���ɵ����߱�֤!!! */
OS_SEC_ALW_INLINE INLINE VOID osMsgNodeFree(MSG_NODE_S* pstMsgNode)
{
    pstMsgNode->stList.pstPrev = (LIST_OBJECT_S *)OS_MSG_NODE_USED;
    pstMsgNode->ucReleasable   = OS_MSG_DELETED;  /*�������ظ��ͷ�*/
    pstMsgNode->ucSmsgLen      = 0;
    pstMsgNode->uwMsgID = (UINT32)g_pstFreeLcMsgHead;/*����Ϣ�����뵽���������ͷ*/
    g_pstFreeLcMsgHead  = pstMsgNode;/*��������������ͷ*/

    return;
}

/* ��Ϣ�жϣ���ȡ��Ϣ�������񣬲�ת������Ӧ���� */
#if ((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170))
OS_SEC_ALW_INLINE INLINE VOID osMsgIrptHandler(UINT32 uwPara, UINT32 uwPara2)
{
    UINT8       ucShedReq;
    MSG_HEAD_S *pstMsgHead;
    MSG_NODE_S *pstMsgNode;
    UINT32      uwRetErr;
    UINT32      uwDstPid;
    UINT32      uwIntSave; /* �����ж� */

    uwIntSave = SRE_IntLock();
    if(OS_MSG_TYPE_NO_PAYLOAD == ((uwPara & 0xf0000000) >> 28))//��4λΪ0xa����ʾ����Ϣ��
    {
        if (NULL == (pstMsgNode = g_pstFreeLcMsgHead))
        {
            uwRetErr = OS_ERRNO_MSG_NO_MSGNODE;
            OS_REPORT_ERROR(uwRetErr);
            (VOID)SRE_IntRestore(uwIntSave);
            return;
        }
        g_pstFreeLcMsgHead = (MSG_NODE_S *)pstMsgNode->uwMsgID;

        /* �����ڵ���Ϣ */
        pstMsgNode->uwDstPid = COMPOSE_PID(SRE_GetCoreID(), (uwPara & 0xff)); //by zhangweiwei,������Ϣ��ʱ����Ϣ����һ��
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

        /*DTS2010100902412  ����Ŀ���߳���Ч�Լ�⣬�ͷ���Դ by00144072*/
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
        pstMsgNode->auwData[2] = auwQData[1];   // ���ڴ����һ�Ŀ��ǣ�����Ϣ����Ϣ��ͬ������auwQData[0]��auwQData[1]

        /*����Ϣ�Ͷ���Ϣ��У��ͳһ�ж�*/
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


