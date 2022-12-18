/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tde_osilist.h
* Description:TDE osi list interface define
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#include "tde_define.h"
#include "tde_handle.h"
#include "tde_buffer.h"
#include "tde_osilist.h"
#include "tde_hal.h"
#include "wmalloc.h"

/* JOB LIST头节点定义 */
typedef struct hiTDE_SWJOBLIST_S
{
    struct list_head stList;
    HI_S32 s32HandleLast;                   /* 最后一个等待提交的job句柄 */
    HI_S32 s32HandleFinished;               /* 上次完成的job句柄 */
    HI_U32 u32JobNum;                       /* 队列中的job个数 */

    TDE_SWJOB_S *pstJobCommitted;           /* 上次提交的job节点指针，由于一次可能提交多个job，因此这里是指第一个job*/
    TDE_SWJOB_S *pstJobToCommit;            /* 等待提交的job节点指针，由于可能由多个job等待提交，因此这里指第一个job*/
    TDE_SWJOB_S *pstJobLast;                /* job链表中最后一个job*/
} TDE_SWJOBLIST_S;

/****************************************************************************/
/*                             TDE osi list 内部变量定义                    */
/****************************************************************************/
STATIC TDE_SWJOBLIST_S *s_pstTDEOsiJobList[TDE_LIST_BUTT] = {NULL}; /* 全局JOB链表队列*/

/****************************************************************************/
/*                             TDE osi list 内部接口定义                    */
/****************************************************************************/
STATIC HI_VOID     TdeOsiListDoFreePhyBuff(HI_U32 u32BuffNum);
STATIC INLINE HI_VOID TdeOsiListSafeDestroyJob(TDE_SWJOB_S *pstJob);
STATIC HI_VOID     TdeOsiListReleaseHandle(HI_HANDLE_MGR *pstJobHeader);
STATIC INLINE HI_VOID TdeOsiListAddJob(TDE_SWJOB_S *pstJob, TDE_LIST_TYPE_E enListType);
STATIC HI_VOID     TdeOsiListDestroyJob(TDE_SWJOB_S *pstJob);
STATIC INLINE HI_VOID list_join(struct list_head *list, struct list_head *head);


/*****************************************************************************
* Function:      TdeOsiListSafeDestroyJob
* Description:   释放从FstCmd到LastCmd的节点
* Input:         pstJob:删除Job链表
* Output:        无
* Return:        无
* Others:
*****************************************************************************/
STATIC INLINE HI_VOID TdeOsiListSafeDestroyJob(TDE_SWJOB_S *pstJob)
{    
    /* 释放job */
    TdeOsiListDestroyJob(pstJob);
}

/*****************************************************************************
* Function:      TdeOsiListReleaseHandle
* Description:   释放Handle管理信息
* Input:         pstJobHeader:handle管理结构
* Output:        无
* Return:        无
* Others:
*****************************************************************************/
STATIC HI_VOID  TdeOsiListReleaseHandle(HI_HANDLE_MGR *pstJobHeader)
{
    //TDE_ASSERT(NULL != pstJobHeader);
    if (pstJobHeader != NULL)
    {
        if (release_handle(pstJobHeader->handle))
        {
            /* 释放handle资源 */
            TDE_FREE(pstJobHeader);
        }
    }
}

/*****************************************************************************
* Function:      TdeOsiListDoFreePhyBuff
* Description:   调用接口释放临时buffer
* Input:         u32BuffNum:临时buffer使用的数量
* Output:        无
* Return:        无
* Others:
*****************************************************************************/
STATIC HI_VOID TdeOsiListDoFreePhyBuff(HI_U32 u32BuffNum)
{
    HI_U32 i;

    for(i = 0; i < u32BuffNum; i++)
    {
        TDE_FreePhysicBuff();
    }

    return;
}


/*****************************************************************************
 Prototype    : TdeOsiListInit
 Description  : 链表管理模块初始化
 Input        : HI_VOID
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2008/3/5
    Author       : w54130
    Modification : Created function

*****************************************************************************/
HI_S32 TdeOsiListInit(HI_VOID)
{
    /* 初始化handle管理模块*/
    if (!initial_handle())
    {
        return HI_FAILURE;
    }

    /* 为全局JOB链表头节点分配内存 */
    s_pstTDEOsiJobList[TDE_LIST_AQ] = (TDE_SWJOBLIST_S *) TDE_MALLOC(sizeof(TDE_SWJOBLIST_S) * TDE_LIST_BUTT);
    if (NULL == s_pstTDEOsiJobList[TDE_LIST_AQ])
    {
        /* 去初始化handle管理模块 */
        destroy_handle();

        return HI_FAILURE;
    }

    memset(s_pstTDEOsiJobList[TDE_LIST_AQ], 0, sizeof(TDE_SWJOBLIST_S) * TDE_LIST_BUTT);
    //s_pstTDEOsiJobList[TDE_LIST_SQ] = s_pstTDEOsiJobList[TDE_LIST_AQ] + 1;

    /* 初始化job链表头部 */
    INIT_LIST_HEAD(&s_pstTDEOsiJobList[TDE_LIST_AQ]->stList);
    //INIT_LIST_HEAD(&s_pstTDEOsiJobList[TDE_LIST_SQ]->stList);

    
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : TdeOsiListFreeNode
 Description  : 释放单个节点
 Input        : pNode 节点指针
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2008/3/5
    Author       : w54130
    Modification : Created function

*****************************************************************************/
STATIC INLINE HI_VOID TdeOsiListFreeNode(TDE_SWNODE_S *pNode)
{
    //TDE_ASSERT(NULL != pNode);
    list_del_init(&pNode->stList);
    if (NULL != pNode->stNodeBuf.pBuf)
    {
        TDE_FREE(pNode->stNodeBuf.pBuf);
    }

    TDE_FREE(pNode);
}

/*****************************************************************************
* Function:      TdeOsiListFreeSerialCmd
* Description:   释放从FstCmd到LastCmd的节点
* Input:         pstFstCmd:第一个节点
*                pstLastCmd:最后一个节点
* Output:        无
* Return:        无
* Others:
*****************************************************************************/
STATIC HI_VOID TdeOsiListFreeSerialCmd(TDE_SWNODE_S *pstFstCmd, TDE_SWNODE_S *pstLastCmd)
{
    TDE_SWNODE_S *pstNextCmd;
    TDE_SWNODE_S *pstCurCmd;
    
    if((NULL == pstFstCmd) || (NULL == pstLastCmd))
    {
        return ;
    }

    pstCurCmd = pstNextCmd = pstFstCmd;
    while (pstNextCmd != pstLastCmd)
    {
        pstNextCmd = list_entry(pstCurCmd->stList.next, TDE_SWNODE_S, stList);
        TdeOsiListFreeNode(pstCurCmd);
        pstCurCmd = pstNextCmd;
    }

    /* 释放尾节点 */
    TdeOsiListFreeNode(pstLastCmd);
}

/*****************************************************************************
 Prototype    : TdeOsiListTerm
 Description  : 链表管理模块去初始化
 Input        : HI_VOID
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2008/3/5
    Author       : w54130
    Modification : Created function

*****************************************************************************/
HI_VOID TdeOsiListTerm(HI_VOID)
{
    TDE_SWJOB_S *pstJob=NULL;
    /* 删除头节点以外的节点 */
    while (!list_empty(&s_pstTDEOsiJobList[TDE_LIST_AQ]->stList))
    {
        pstJob = list_entry(s_pstTDEOsiJobList[TDE_LIST_AQ]->stList.next, TDE_SWJOB_S, stList);
        list_del_init(&pstJob->stList);
        TdeOsiListDestroyJob(pstJob);
    }
    TDE_FREE(s_pstTDEOsiJobList[TDE_LIST_AQ]);
    s_pstTDEOsiJobList[TDE_LIST_AQ] = NULL;
    //s_pstTDEOsiJobList[TDE_LIST_SQ] = NULL;
    /* 去初始化handle管理模块 */
    destroy_handle();
    return;
}

/*****************************************************************************
* Function:      TdeOsiListAddJob
* Description:   把任务信息添加到任务链表中
* Input:         pstJob:任务结构
*                enListType:提交类型Sq/Aq
* Output:        无
* Return:        无
* Others:
*****************************************************************************/
STATIC INLINE HI_VOID TdeOsiListAddJob(TDE_SWJOB_S *pstJob, TDE_LIST_TYPE_E enListType)
{
    list_add_tail(&pstJob->stList, &s_pstTDEOsiJobList[enListType]->stList);
    s_pstTDEOsiJobList[enListType]->u32JobNum++;
    s_pstTDEOsiJobList[enListType]->s32HandleLast = pstJob->s32Handle;
    s_pstTDEOsiJobList[enListType]->pstJobLast = pstJob;
}

/*****************************************************************************
 Prototype    : TdeOsiListBeginJob
 Description  : 创建一个job
 Input        : NONE
 Output       : pHandle: 创建的job句柄
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2008/3/5
    Author       : w54130
    Modification : Created function

*****************************************************************************/
HI_S32 TdeOsiListBeginJob(TDE_HANDLE *pHandle)
{
    HI_HANDLE_MGR *pHandleMgr;
    TDE_SWJOB_S *pstJob;

    /* 分配handle，每个handle带一个job资源 */
    pHandleMgr = (HI_HANDLE_MGR *) TDE_MALLOC(sizeof(HI_HANDLE_MGR) + sizeof(TDE_SWJOB_S));
    if (NULL == pHandleMgr)
    {
        TDE_TRACE(TDE_KERN_ERR, "TDE BegJob Malloc Fail!\n");
        return HI_ERR_TDE_NO_MEM;
    }

    memset(pHandleMgr, 0, sizeof(HI_HANDLE_MGR) + sizeof(TDE_SWJOB_S));

    if (get_handle(pHandleMgr, pHandle) < 0)
    {
        TDE_TRACE(TDE_KERN_ERR, "Too Many TDE Jobs!\n");
        return HI_ERR_TDE_NO_MEM;
    }

    pstJob = (TDE_SWJOB_S *)((HI_U8*)pHandleMgr + sizeof(HI_HANDLE_MGR));
    pHandleMgr->res = (HI_VOID*)pstJob;

    /* 初始化链表头部 */
    INIT_LIST_HEAD(&pstJob->stList);
    
    pstJob->s32Handle = *pHandle;

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : TdeOsiListDestroyJob
 Description  : 销毁一个job
 Input        : s32Handle: job句柄
 Output       : NONE
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2008/3/5
    Author       : w54130
    Modification : Created function

*****************************************************************************/
STATIC HI_VOID     TdeOsiListDestroyJob(TDE_SWJOB_S *pstJob)
{
    HI_HANDLE_MGR *pHandleMgr;
    /* 获取链表头指针*/
    
    if (!query_handle(pstJob->s32Handle, &pHandleMgr))
    {
        TDE_TRACE(TDE_KERN_DEBUG, "handle %d does not exist!\n", pstJob->s32Handle);
        return;
    }

    TdeOsiListFreeSerialCmd(pstJob->pstFirstCmd, pstJob->pstTailNode);

    /* 释放handle */
    TdeOsiListReleaseHandle(pHandleMgr);
}

/*****************************************************************************
* Function:      TdeOsiListCancelJob
* Description:   取消任务
* Input:         s32Handle:任务句柄
* Output:        无
* Return:        =0,成功 <0,错误
* Others:
*****************************************************************************/
#ifndef HIGO_CODE_CUT 
HI_S32     TdeOsiListCancelJob(TDE_HANDLE s32Handle)
{
    HI_HANDLE_MGR *pHandleMgr;
    TDE_SWJOB_S *pstJob;

    /* 获取链表头指针*/
    if (!query_handle(s32Handle, &pHandleMgr))
    {
        /* Job不存在 */
        return HI_SUCCESS;
    }
    
    pstJob = (TDE_SWJOB_S *)pHandleMgr->res;

    if(pstJob->bSubmitted)
    {
        /* job已经提交不能取消 */
        TDE_TRACE(TDE_KERN_ERR, "Handle %d has been submitted!\n", s32Handle);
        return HI_FAILURE;
    }

    TdeOsiListFreeSerialCmd(pstJob->pstFirstCmd, pstJob->pstTailNode);
    
    /* 释放handle */
    TdeOsiListReleaseHandle(pHandleMgr);

    return 0;
}
#endif
/*****************************************************************************
 Prototype    : TdeOsiListAddNode
 Description  : 向指定的job中添加一个命令
 Input        : s32Handle: job句柄
                pSwNode:节点资源
                enSubmType:节点的类型
 Output       : NONE
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2008/3/5
    Author       : w54130
    Modification : Created function

*****************************************************************************/
HI_S32 TdeOsiListAddNode(TDE_HANDLE s32Handle, TDE_NODE_BUF_S * pSwNode,
                         TDE_NODE_SUBM_TYPE_E enSubmType, HI_U32 u32PhyBuffNumInNode)
{
    HI_HANDLE_MGR *pHandleMgr;
    TDE_SWJOB_S *pstJob;
    TDE_SWNODE_S *pstCmd;
    HI_BOOL bValid;

    bValid = query_handle(s32Handle, &pHandleMgr);

    if (!bValid)
    {
        TDE_TRACE(TDE_KERN_ERR, "invalid handle %d!\n", s32Handle);
        return HI_ERR_TDE_INVALID_HANDLE;
    }
    
    pstJob = (TDE_SWJOB_S*)pHandleMgr->res;
    if(pstJob->bSubmitted)
    {
        TDE_TRACE(TDE_KERN_ERR, "job %d already submitted!\n", s32Handle);
        return HI_ERR_TDE_INVALID_HANDLE;
    }

    /* 为节点分配内存*/
    pstCmd = (TDE_SWNODE_S *) TDE_MALLOC(sizeof(TDE_SWNODE_S));
    if (NULL == pstCmd)
    {
        TDE_TRACE(TDE_KERN_ERR, "malloc failed!\n");
        return HI_ERR_TDE_NO_MEM;
    }

    if (enSubmType != TDE_NODE_SUBM_CHILD)
    {
        /* 非子节点增加job命令计数*/
        pstJob->u32CmdNum++;

        /* 记录第一个命令节点 */
        if (1 == pstJob->u32CmdNum)
        {
            pstJob->pstFirstCmd = pstCmd;
            /* 初始化链表头部 */
            INIT_LIST_HEAD(&pstCmd->stList);
        }

        /* 记录最后一个命令节点 */
        pstJob->pstLastCmd = pstCmd;
        
    }

    /*记录父节点信息*/
    switch(enSubmType)
    {
        case TDE_NODE_SUBM_PARENT:
            pstJob->pstParentCmd = pstCmd;
            pstCmd->pstParentNodeInCmd = HI_NULL;
            break;
        case TDE_NODE_SUBM_CHILD:
            pstCmd->pstParentNodeInCmd = pstJob->pstParentCmd;
            break;
        case TDE_NODE_SUBM_ALONE:
            pstCmd->pstParentNodeInCmd = HI_NULL;
            break;
    }

    /*填写上一节点的地址和更新标识位*/
    if (HI_NULL != pstJob->pstTailNode)
    {
       HI_U32 *pNextNodeAddr = (HI_U32 *)pstJob->pstTailNode->stNodeBuf.pBuf + (TDE_NODE_HEAD_BYTE >> 2) + ((pstJob->pstTailNode->stNodeBuf.u32NodeSz) >> 2);
       HI_U32 *pNextNodeUpdate = pNextNodeAddr + 1;

       *pNextNodeAddr = pSwNode->u32PhyAddr;

#ifdef TDE_VERSION_MPW
       *pNextNodeUpdate = pSwNode->u64Update & 0xffffffff;
#else
       *pNextNodeUpdate++ = pSwNode->u64Update & 0xffffffff;
       *pNextNodeUpdate = (pSwNode->u64Update >> 32) & 0xffffffff;
#endif
    }

    /* 生成新节点*/
    memcpy(&pstCmd->stNodeBuf, pSwNode, sizeof(*pSwNode));
    pstCmd->enNotiType = TDE_JOB_NONE_NOTIFY;
    pstCmd->s32Handle = pstJob->s32Handle;
    pstCmd->s32Index   = pstJob->u32CmdNum;
    pstCmd->enSubmType = enSubmType;
    pstCmd->u32PhyBuffNum = u32PhyBuffNumInNode;

    /*硬件读取的buffer头中需要保存软件节点指针*/
    *(HI_U32 *)pstCmd->stNodeBuf.pBuf = (HI_U32)pstCmd;
    
    /* 将该节点添加到对应的job链表中*/
    list_add_tail(&pstCmd->stList, &pstJob->pstFirstCmd->stList);
    pstJob->pstTailNode = pstCmd;
    pstJob->u32NodeNum++;

    if (pstCmd->u32PhyBuffNum != 0)
    {
        pstJob->bAqUseBuff = HI_TRUE;
    }
    
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : list_join
 Description  : 将链表list加入到链表head的尾部，list无头节点，head有头节点
 Input        : list: 待加入链表头节点
                head:目标链表头节点
 Output       : NONE
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2008/3/5
    Author       : w54130
    Modification : Created function

*****************************************************************************/
STATIC INLINE HI_VOID list_join(struct list_head *list, struct list_head *head)
{
    if(NULL != list)
    {
        struct list_head *last = list->prev;
        struct list_head *at = head->prev;

        list->prev = at;
        at->next = list;

        last->next = head;
        head->prev = last;
    }
}


/*****************************************************************************
* Function:      TdeOsiListWaitTdeIdle
* Description:   等待任务完成
* Input:         无
* Output:        无
* Return:        True: Idle/False: Busy
* Others:        无
*****************************************************************************/
HI_VOID  static TdeOsiListWaitTdeIdle(HI_VOID)
{
    /* 死等任务完成 */
    while(1)
    {
        /* 以10ms 为单位查询 */
#ifdef BOOT
        udelay(10*1000);
#else
        usleep(1000*10);
#endif
        if (TdeHalCtlIsIdleSafely())
        {
            return;
        }
    }
}


/*****************************************************************************
 Prototype    : TdeOsiListSubmitJob
 Description  : 用户提交job处理，首先将job链表添加到全局链表，然后根据不同的条件做不同的处理:
                1.TDE空闲的情况且无命令可添加的情况下，赋值待添加节点指针，启动软件链表节点向硬件的添加过程
                2.TDE不空闲但无命令可添加的情况下，只需要赋值待添加节点指针就可以了
                3.TDE不空闲却有命令可添加，不需要做任何处理
 Input        : s32Handle: job句柄
                pSwNode:节点资源
                enSubmType:节点的类型
 Output       : NONE
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2008/3/5
    Author       : w54130
    Modification : Created function

*****************************************************************************/
HI_S32 TdeOsiListSubmitJob(TDE_HANDLE s32Handle, TDE_LIST_TYPE_E enListType,
                           HI_U32 u32TimeOut, TDE_FUNC_CB pFuncComplCB, HI_VOID *pFuncPara,
                           TDE_NOTIFY_MODE_E enNotiType)
{
    TDE_SWJOB_S * pstJob;
    HI_HANDLE_MGR *pHandleMgr;
    HI_BOOL bValid;
    TDE_SWNODE_S *pstTailNode = NULL;
    HI_S32 s32Ret;
    //HI_U8 *pBuf;

    /* 获取job信息 */
    bValid = query_handle(s32Handle, &pHandleMgr);
    if (!bValid)
    {
        TDE_TRACE(TDE_KERN_INFO, "invalid handle %d!\n", s32Handle);
        return HI_ERR_TDE_INVALID_HANDLE;
    }

    /* OK, Job信息合法 */
    pstJob = (TDE_SWJOB_S *)pHandleMgr->res;
    if(pstJob->bSubmitted)
    {
        TDE_TRACE(TDE_KERN_INFO, "job %d already submitted!\n", s32Handle);
        return HI_ERR_TDE_INVALID_HANDLE;
    }
    
    /* 没有命令可供执行 */
    if(NULL == pstJob->pstFirstCmd)
    {
        TDE_TRACE(TDE_KERN_INFO, "no cmd !\n");
        /* 释放handle */
        TdeOsiListReleaseHandle(pHandleMgr);
        return HI_SUCCESS;
    }

    /* 修改待提交job最后一个节点的信息*/
    pstTailNode = pstJob->pstTailNode;
    pstTailNode->enNotiType = enNotiType;

    //pBuf = (HI_U8 *)pstTailNode->stNodeBuf.pBuf + TDE_NODE_HEAD_BYTE;
    
    pstJob->bSubmitted = HI_TRUE;
    pstJob->enNotiType   = enNotiType;
    pstJob->pFuncComplCB = pFuncComplCB;
    pstJob->pFuncPara = pFuncPara;

    /*若有等待提交的job 则将待提交job的首节点和最后一个job的尾节点相连
       否则，将新提交的job作为待提交job*/
    if (HI_NULL != s_pstTDEOsiJobList[enListType]->pstJobToCommit)
    {
        TDE_SWNODE_S *pstTailNodeInJobList = s_pstTDEOsiJobList[enListType]->pstJobLast->pstTailNode;
        HI_U32 *pNextNodeAddr = (HI_U32 *)pstTailNodeInJobList->stNodeBuf.pBuf + (TDE_NODE_HEAD_BYTE >> 2) + ((pstTailNodeInJobList->stNodeBuf.u32NodeSz) >> 2);
        HI_U32 *pNextNodeUpdate = pNextNodeAddr + 1;

        *pNextNodeAddr = pstJob->pstFirstCmd->stNodeBuf.u32PhyAddr;

#ifdef TDE_VERSION_MPW
        *pNextNodeUpdate = (HI_U32)(pstJob->pstFirstCmd->stNodeBuf.u64Update & 0xffffffff);
#else
        *pNextNodeUpdate = (HI_U32)(pstJob->pstFirstCmd->stNodeBuf.u64Update & 0xffffffff);
        *(pNextNodeUpdate + 1) = (HI_U32)((pstJob->pstFirstCmd->stNodeBuf.u64Update >> 32) & 0xffffffff);        
#endif

        if (pstJob->bAqUseBuff)
        {
            s_pstTDEOsiJobList[enListType]->pstJobToCommit->bAqUseBuff = HI_TRUE;
        }
    }
    else
    {
        s_pstTDEOsiJobList[enListType]->pstJobToCommit = pstJob;
    }

    /* 将job添加到全局job链表中 */
    TdeOsiListAddJob(pstJob, enListType);

    s32Ret = TdeHalNodeExecute(enListType, s_pstTDEOsiJobList[enListType]->pstJobToCommit->pstFirstCmd->stNodeBuf.u32PhyAddr,
    s_pstTDEOsiJobList[enListType]->pstJobToCommit->pstFirstCmd->stNodeBuf.u64Update, \
    s_pstTDEOsiJobList[enListType]->pstJobToCommit->bAqUseBuff);
    if (s32Ret == HI_SUCCESS)
    {
        s_pstTDEOsiJobList[enListType]->pstJobCommitted = s_pstTDEOsiJobList[enListType]->pstJobToCommit;
        s_pstTDEOsiJobList[enListType]->pstJobToCommit = HI_NULL;
    }
    
    /* to do:等待TDE任务完成 */
    TdeOsiListWaitTdeIdle();

    /* 从链表中删除该job节点,防止再次遍历到该节点 */
    list_del_init(&pstJob->stList);

    /* 释放job */
    TdeOsiListSafeDestroyJob(pstJob);

    TDE_TRACE(TDE_KERN_DEBUG, "handle:%d complete!\n", pstJob->s32Handle);

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : TdeOsiListReset
 Description  : Reset所有状态,释放链表空间
 Input        : 无
 Output       : NONE
 Return Value : HI_SUCCESS/HI_FAILURE
 Calls        :
 Called By    :
*****************************************************************************/
#ifndef HIGO_CODE_CUT
HI_VOID TdeOsiListReset(HI_VOID)
{
    TDE_SWJOB_S *pstDelJob;
    HI_U32 i = 0;
    TDE_LIST_TYPE_E enListType[3] = {TDE_LIST_AQ, TDE_LIST_SQ, TDE_LIST_BUTT};
    
    for (i = 0; i < 2; i++)
    {
        while(!list_empty(&s_pstTDEOsiJobList[enListType[i]]->stList))
        {
            pstDelJob = list_entry(s_pstTDEOsiJobList[enListType[i]]->stList.next, TDE_SWJOB_S, stList);
            s_pstTDEOsiJobList[enListType[i]]->u32JobNum--;

            /* 从链表中删除该job节点,防止再次遍历到该节点 */
            list_del_init(&pstDelJob->stList);            
            
            TDE_TRACE(TDE_KERN_DEBUG, "reset free handle:%d!\n", pstDelJob->s32Handle);

            TdeOsiListSafeDestroyJob(pstDelJob);
                        
        }

        s_pstTDEOsiJobList[enListType[i]]->s32HandleFinished = -1;
        s_pstTDEOsiJobList[enListType[i]]->s32HandleLast = -1;

        s_pstTDEOsiJobList[enListType[i]]->pstJobCommitted = HI_NULL;
        s_pstTDEOsiJobList[enListType[i]]->pstJobToCommit = HI_NULL;
        s_pstTDEOsiJobList[enListType[i]]->pstJobLast = HI_NULL;
    }

    /* 如果硬件处于IDLE状态则复位HAL的状态 */
    if (TdeHalCtlIsIdleSafely())
    {
        TDE_TRACE(TDE_KERN_DEBUG, "reset tde is IDLE\n");
        TdeHalResetStatus();
    }
    else
    {
        TDE_TRACE(TDE_KERN_DEBUG, "reset tde is BUSY\n");
    }
    
    return;
}
#endif
/*****************************************************************************
* Function:      TdeOsiListGetPhyBuff
* Description:   获取一块物理buffer，用于抗闪烁和缩放
* Input:         TDE_BUFFER_USAGE_E enBuffUsage
* Output:        无
* Return:        创建的任务句柄
* Others:        无
*****************************************************************************/
HI_U32 TdeOsiListGetPhyBuff(TDE_BUFFER_USAGE_E enBuffUsage)
{
    return TDE_AllocPhysicBuff(enBuffUsage);
}

/*****************************************************************************
* Function:      TdeOsiListPutPhyBuff
* Description:   放回物理buffer
* Input:         u32BuffNum 
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID  TdeOsiListPutPhyBuff(HI_U32 u32BuffNum)
{
    if (0 == u32BuffNum)
    {
        return;
    }

    TdeOsiListDoFreePhyBuff(u32BuffNum);
}


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

