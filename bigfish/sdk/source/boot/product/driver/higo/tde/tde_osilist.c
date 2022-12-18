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

/* JOB LISTͷ�ڵ㶨�� */
typedef struct hiTDE_SWJOBLIST_S
{
    struct list_head stList;
    HI_S32 s32HandleLast;                   /* ���һ���ȴ��ύ��job��� */
    HI_S32 s32HandleFinished;               /* �ϴ���ɵ�job��� */
    HI_U32 u32JobNum;                       /* �����е�job���� */

    TDE_SWJOB_S *pstJobCommitted;           /* �ϴ��ύ��job�ڵ�ָ�룬����һ�ο����ύ���job�����������ָ��һ��job*/
    TDE_SWJOB_S *pstJobToCommit;            /* �ȴ��ύ��job�ڵ�ָ�룬���ڿ����ɶ��job�ȴ��ύ���������ָ��һ��job*/
    TDE_SWJOB_S *pstJobLast;                /* job���������һ��job*/
} TDE_SWJOBLIST_S;

/****************************************************************************/
/*                             TDE osi list �ڲ���������                    */
/****************************************************************************/
STATIC TDE_SWJOBLIST_S *s_pstTDEOsiJobList[TDE_LIST_BUTT] = {NULL}; /* ȫ��JOB�������*/

/****************************************************************************/
/*                             TDE osi list �ڲ��ӿڶ���                    */
/****************************************************************************/
STATIC HI_VOID     TdeOsiListDoFreePhyBuff(HI_U32 u32BuffNum);
STATIC INLINE HI_VOID TdeOsiListSafeDestroyJob(TDE_SWJOB_S *pstJob);
STATIC HI_VOID     TdeOsiListReleaseHandle(HI_HANDLE_MGR *pstJobHeader);
STATIC INLINE HI_VOID TdeOsiListAddJob(TDE_SWJOB_S *pstJob, TDE_LIST_TYPE_E enListType);
STATIC HI_VOID     TdeOsiListDestroyJob(TDE_SWJOB_S *pstJob);
STATIC INLINE HI_VOID list_join(struct list_head *list, struct list_head *head);


/*****************************************************************************
* Function:      TdeOsiListSafeDestroyJob
* Description:   �ͷŴ�FstCmd��LastCmd�Ľڵ�
* Input:         pstJob:ɾ��Job����
* Output:        ��
* Return:        ��
* Others:
*****************************************************************************/
STATIC INLINE HI_VOID TdeOsiListSafeDestroyJob(TDE_SWJOB_S *pstJob)
{    
    /* �ͷ�job */
    TdeOsiListDestroyJob(pstJob);
}

/*****************************************************************************
* Function:      TdeOsiListReleaseHandle
* Description:   �ͷ�Handle������Ϣ
* Input:         pstJobHeader:handle����ṹ
* Output:        ��
* Return:        ��
* Others:
*****************************************************************************/
STATIC HI_VOID  TdeOsiListReleaseHandle(HI_HANDLE_MGR *pstJobHeader)
{
    //TDE_ASSERT(NULL != pstJobHeader);
    if (pstJobHeader != NULL)
    {
        if (release_handle(pstJobHeader->handle))
        {
            /* �ͷ�handle��Դ */
            TDE_FREE(pstJobHeader);
        }
    }
}

/*****************************************************************************
* Function:      TdeOsiListDoFreePhyBuff
* Description:   ���ýӿ��ͷ���ʱbuffer
* Input:         u32BuffNum:��ʱbufferʹ�õ�����
* Output:        ��
* Return:        ��
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
 Description  : �������ģ���ʼ��
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
    /* ��ʼ��handle����ģ��*/
    if (!initial_handle())
    {
        return HI_FAILURE;
    }

    /* Ϊȫ��JOB����ͷ�ڵ�����ڴ� */
    s_pstTDEOsiJobList[TDE_LIST_AQ] = (TDE_SWJOBLIST_S *) TDE_MALLOC(sizeof(TDE_SWJOBLIST_S) * TDE_LIST_BUTT);
    if (NULL == s_pstTDEOsiJobList[TDE_LIST_AQ])
    {
        /* ȥ��ʼ��handle����ģ�� */
        destroy_handle();

        return HI_FAILURE;
    }

    memset(s_pstTDEOsiJobList[TDE_LIST_AQ], 0, sizeof(TDE_SWJOBLIST_S) * TDE_LIST_BUTT);
    //s_pstTDEOsiJobList[TDE_LIST_SQ] = s_pstTDEOsiJobList[TDE_LIST_AQ] + 1;

    /* ��ʼ��job����ͷ�� */
    INIT_LIST_HEAD(&s_pstTDEOsiJobList[TDE_LIST_AQ]->stList);
    //INIT_LIST_HEAD(&s_pstTDEOsiJobList[TDE_LIST_SQ]->stList);

    
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : TdeOsiListFreeNode
 Description  : �ͷŵ����ڵ�
 Input        : pNode �ڵ�ָ��
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
* Description:   �ͷŴ�FstCmd��LastCmd�Ľڵ�
* Input:         pstFstCmd:��һ���ڵ�
*                pstLastCmd:���һ���ڵ�
* Output:        ��
* Return:        ��
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

    /* �ͷ�β�ڵ� */
    TdeOsiListFreeNode(pstLastCmd);
}

/*****************************************************************************
 Prototype    : TdeOsiListTerm
 Description  : �������ģ��ȥ��ʼ��
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
    /* ɾ��ͷ�ڵ�����Ľڵ� */
    while (!list_empty(&s_pstTDEOsiJobList[TDE_LIST_AQ]->stList))
    {
        pstJob = list_entry(s_pstTDEOsiJobList[TDE_LIST_AQ]->stList.next, TDE_SWJOB_S, stList);
        list_del_init(&pstJob->stList);
        TdeOsiListDestroyJob(pstJob);
    }
    TDE_FREE(s_pstTDEOsiJobList[TDE_LIST_AQ]);
    s_pstTDEOsiJobList[TDE_LIST_AQ] = NULL;
    //s_pstTDEOsiJobList[TDE_LIST_SQ] = NULL;
    /* ȥ��ʼ��handle����ģ�� */
    destroy_handle();
    return;
}

/*****************************************************************************
* Function:      TdeOsiListAddJob
* Description:   ��������Ϣ��ӵ�����������
* Input:         pstJob:����ṹ
*                enListType:�ύ����Sq/Aq
* Output:        ��
* Return:        ��
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
 Description  : ����һ��job
 Input        : NONE
 Output       : pHandle: ������job���
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

    /* ����handle��ÿ��handle��һ��job��Դ */
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

    /* ��ʼ������ͷ�� */
    INIT_LIST_HEAD(&pstJob->stList);
    
    pstJob->s32Handle = *pHandle;

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : TdeOsiListDestroyJob
 Description  : ����һ��job
 Input        : s32Handle: job���
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
    /* ��ȡ����ͷָ��*/
    
    if (!query_handle(pstJob->s32Handle, &pHandleMgr))
    {
        TDE_TRACE(TDE_KERN_DEBUG, "handle %d does not exist!\n", pstJob->s32Handle);
        return;
    }

    TdeOsiListFreeSerialCmd(pstJob->pstFirstCmd, pstJob->pstTailNode);

    /* �ͷ�handle */
    TdeOsiListReleaseHandle(pHandleMgr);
}

/*****************************************************************************
* Function:      TdeOsiListCancelJob
* Description:   ȡ������
* Input:         s32Handle:������
* Output:        ��
* Return:        =0,�ɹ� <0,����
* Others:
*****************************************************************************/
#ifndef HIGO_CODE_CUT 
HI_S32     TdeOsiListCancelJob(TDE_HANDLE s32Handle)
{
    HI_HANDLE_MGR *pHandleMgr;
    TDE_SWJOB_S *pstJob;

    /* ��ȡ����ͷָ��*/
    if (!query_handle(s32Handle, &pHandleMgr))
    {
        /* Job������ */
        return HI_SUCCESS;
    }
    
    pstJob = (TDE_SWJOB_S *)pHandleMgr->res;

    if(pstJob->bSubmitted)
    {
        /* job�Ѿ��ύ����ȡ�� */
        TDE_TRACE(TDE_KERN_ERR, "Handle %d has been submitted!\n", s32Handle);
        return HI_FAILURE;
    }

    TdeOsiListFreeSerialCmd(pstJob->pstFirstCmd, pstJob->pstTailNode);
    
    /* �ͷ�handle */
    TdeOsiListReleaseHandle(pHandleMgr);

    return 0;
}
#endif
/*****************************************************************************
 Prototype    : TdeOsiListAddNode
 Description  : ��ָ����job�����һ������
 Input        : s32Handle: job���
                pSwNode:�ڵ���Դ
                enSubmType:�ڵ������
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

    /* Ϊ�ڵ�����ڴ�*/
    pstCmd = (TDE_SWNODE_S *) TDE_MALLOC(sizeof(TDE_SWNODE_S));
    if (NULL == pstCmd)
    {
        TDE_TRACE(TDE_KERN_ERR, "malloc failed!\n");
        return HI_ERR_TDE_NO_MEM;
    }

    if (enSubmType != TDE_NODE_SUBM_CHILD)
    {
        /* ���ӽڵ�����job�������*/
        pstJob->u32CmdNum++;

        /* ��¼��һ������ڵ� */
        if (1 == pstJob->u32CmdNum)
        {
            pstJob->pstFirstCmd = pstCmd;
            /* ��ʼ������ͷ�� */
            INIT_LIST_HEAD(&pstCmd->stList);
        }

        /* ��¼���һ������ڵ� */
        pstJob->pstLastCmd = pstCmd;
        
    }

    /*��¼���ڵ���Ϣ*/
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

    /*��д��һ�ڵ�ĵ�ַ�͸��±�ʶλ*/
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

    /* �����½ڵ�*/
    memcpy(&pstCmd->stNodeBuf, pSwNode, sizeof(*pSwNode));
    pstCmd->enNotiType = TDE_JOB_NONE_NOTIFY;
    pstCmd->s32Handle = pstJob->s32Handle;
    pstCmd->s32Index   = pstJob->u32CmdNum;
    pstCmd->enSubmType = enSubmType;
    pstCmd->u32PhyBuffNum = u32PhyBuffNumInNode;

    /*Ӳ����ȡ��bufferͷ����Ҫ��������ڵ�ָ��*/
    *(HI_U32 *)pstCmd->stNodeBuf.pBuf = (HI_U32)pstCmd;
    
    /* ���ýڵ���ӵ���Ӧ��job������*/
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
 Description  : ������list���뵽����head��β����list��ͷ�ڵ㣬head��ͷ�ڵ�
 Input        : list: ����������ͷ�ڵ�
                head:Ŀ������ͷ�ڵ�
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
* Description:   �ȴ��������
* Input:         ��
* Output:        ��
* Return:        True: Idle/False: Busy
* Others:        ��
*****************************************************************************/
HI_VOID  static TdeOsiListWaitTdeIdle(HI_VOID)
{
    /* ����������� */
    while(1)
    {
        /* ��10ms Ϊ��λ��ѯ */
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
 Description  : �û��ύjob�������Ƚ�job������ӵ�ȫ������Ȼ����ݲ�ͬ����������ͬ�Ĵ���:
                1.TDE���е���������������ӵ�����£���ֵ����ӽڵ�ָ�룬�����������ڵ���Ӳ������ӹ���
                2.TDE�����е����������ӵ�����£�ֻ��Ҫ��ֵ����ӽڵ�ָ��Ϳ�����
                3.TDE������ȴ���������ӣ�����Ҫ���κδ���
 Input        : s32Handle: job���
                pSwNode:�ڵ���Դ
                enSubmType:�ڵ������
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

    /* ��ȡjob��Ϣ */
    bValid = query_handle(s32Handle, &pHandleMgr);
    if (!bValid)
    {
        TDE_TRACE(TDE_KERN_INFO, "invalid handle %d!\n", s32Handle);
        return HI_ERR_TDE_INVALID_HANDLE;
    }

    /* OK, Job��Ϣ�Ϸ� */
    pstJob = (TDE_SWJOB_S *)pHandleMgr->res;
    if(pstJob->bSubmitted)
    {
        TDE_TRACE(TDE_KERN_INFO, "job %d already submitted!\n", s32Handle);
        return HI_ERR_TDE_INVALID_HANDLE;
    }
    
    /* û������ɹ�ִ�� */
    if(NULL == pstJob->pstFirstCmd)
    {
        TDE_TRACE(TDE_KERN_INFO, "no cmd !\n");
        /* �ͷ�handle */
        TdeOsiListReleaseHandle(pHandleMgr);
        return HI_SUCCESS;
    }

    /* �޸Ĵ��ύjob���һ���ڵ����Ϣ*/
    pstTailNode = pstJob->pstTailNode;
    pstTailNode->enNotiType = enNotiType;

    //pBuf = (HI_U8 *)pstTailNode->stNodeBuf.pBuf + TDE_NODE_HEAD_BYTE;
    
    pstJob->bSubmitted = HI_TRUE;
    pstJob->enNotiType   = enNotiType;
    pstJob->pFuncComplCB = pFuncComplCB;
    pstJob->pFuncPara = pFuncPara;

    /*���еȴ��ύ��job �򽫴��ύjob���׽ڵ�����һ��job��β�ڵ�����
       ���򣬽����ύ��job��Ϊ���ύjob*/
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

    /* ��job��ӵ�ȫ��job������ */
    TdeOsiListAddJob(pstJob, enListType);

    s32Ret = TdeHalNodeExecute(enListType, s_pstTDEOsiJobList[enListType]->pstJobToCommit->pstFirstCmd->stNodeBuf.u32PhyAddr,
    s_pstTDEOsiJobList[enListType]->pstJobToCommit->pstFirstCmd->stNodeBuf.u64Update, \
    s_pstTDEOsiJobList[enListType]->pstJobToCommit->bAqUseBuff);
    if (s32Ret == HI_SUCCESS)
    {
        s_pstTDEOsiJobList[enListType]->pstJobCommitted = s_pstTDEOsiJobList[enListType]->pstJobToCommit;
        s_pstTDEOsiJobList[enListType]->pstJobToCommit = HI_NULL;
    }
    
    /* to do:�ȴ�TDE������� */
    TdeOsiListWaitTdeIdle();

    /* ��������ɾ����job�ڵ�,��ֹ�ٴα������ýڵ� */
    list_del_init(&pstJob->stList);

    /* �ͷ�job */
    TdeOsiListSafeDestroyJob(pstJob);

    TDE_TRACE(TDE_KERN_DEBUG, "handle:%d complete!\n", pstJob->s32Handle);

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : TdeOsiListReset
 Description  : Reset����״̬,�ͷ�����ռ�
 Input        : ��
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

            /* ��������ɾ����job�ڵ�,��ֹ�ٴα������ýڵ� */
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

    /* ���Ӳ������IDLE״̬��λHAL��״̬ */
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
* Description:   ��ȡһ������buffer�����ڿ���˸������
* Input:         TDE_BUFFER_USAGE_E enBuffUsage
* Output:        ��
* Return:        ������������
* Others:        ��
*****************************************************************************/
HI_U32 TdeOsiListGetPhyBuff(TDE_BUFFER_USAGE_E enBuffUsage)
{
    return TDE_AllocPhysicBuff(enBuffUsage);
}

/*****************************************************************************
* Function:      TdeOsiListPutPhyBuff
* Description:   �Ż�����buffer
* Input:         u32BuffNum 
* Output:        ��
* Return:        ��
* Others:        ��
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

