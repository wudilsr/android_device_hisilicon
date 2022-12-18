/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tde_os_listi.h
* Description:TDE osi list interface define
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/

#ifndef _TDE_OSILIST_H_
#define _TDE_OSILIST_H_

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#include "list.h"
#include "tde_define.h"
#include "hi_tde_type.h"


/****************************************************************************/
/*                             TDE osi list types define                         */
/****************************************************************************/

/* 软件链表节点数据结构 */
typedef struct hiTDE_SWNODE_S
{
    struct list_head stList;    
    HI_S32 s32Handle;           /* 该命令所在的job句柄*/
    HI_S32 s32Index;            /* 该命令在job中的序号，从1开始编号，编号相同的是同一个命令 */
    TDE_NODE_SUBM_TYPE_E enSubmType; /* 当前节点类型 */
    TDE_NOTIFY_MODE_E enNotiType;   /* 节点完成后的通知类型 */
    TDE_NODE_BUF_S stNodeBuf;       /* 操作配置信息节点 */
    HI_U32 u32PhyBuffNum;           /* 所分配的物理buffer数量 */
    struct hiTDE_SWNODE_S *pstParentNodeInCmd;/* 该命令的第一个软件节点 */
} TDE_SWNODE_S;

/* job定义 */
typedef struct hiTDE_SWJOB_S
{
    struct list_head stList;    
    HI_S32 s32Handle;               /* job句柄 */
    TDE_FUNC_CB       pFuncComplCB; /* 回调函数指针 */
    HI_VOID * pFuncPara;            /* 回调函数参数 */
    TDE_NOTIFY_MODE_E enNotiType;   /* 节点完成后的通知类型 */
    HI_U32 u32CmdNum;               /* job中含有的命令数 */
    HI_U32 u32NodeNum;              /* job中含有的节点数 */
    TDE_SWNODE_S *pstFirstCmd;      /* job中的第一个命令所在的软件节点 */
    TDE_SWNODE_S *pstLastCmd;       /* job中的最后一个命令所在的软件节点 */
    TDE_SWNODE_S *pstTailNode;      /* job中的最后一个软件节点 */
    HI_BOOL bInQuery;               /* 是否有用户在查询 */
    HI_BOOL bSubmitted;             /* 是否已经提交 */
    HI_BOOL bAqUseBuff;             /* 是否使用临时buffer*/
    TDE_SWNODE_S *pstParentCmd;     /*用来记录父节点*/
}TDE_SWJOB_S;

/****************************************************************************/
/*                             TDE osi list functions define                */
/****************************************************************************/

/*****************************************************************************
* Function:      TdeOsiSuspListInit
* Description:   初始化软件内部用于缓存TDE操作的全局链表
* Input:         null
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_S32      TdeOsiListInit(HI_VOID);

/*****************************************************************************
* Function:      TdeOsiListTerm
* Description:   释放软件内部用于缓存TDE操作的全局链表
* Input:         NULL
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_VOID     TdeOsiListTerm(HI_VOID);

/*****************************************************************************
* Function:      TdeOsiListBeginJob
* Description:   创建链表,返回链表头指针
* Input:         无
* Output:        无
* Return:        创建的任务句柄
* Others:        无
*****************************************************************************/
HI_S32      TdeOsiListBeginJob(TDE_HANDLE *pHandle );

/*****************************************************************************
* Function:      TdeOsiListCancelJob
* Description:   删除s32Handle指定的链表
* Input:         s32Handle:待删除的链表
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_S32      TdeOsiListCancelJob(TDE_HANDLE s32Handle);

/*****************************************************************************
* Function:      TdeOsiListAddNode
* Description:   创建链表,返回链表头指针
* Input:         s32Handle: 需要操作的Job的头节点指针
*                pSwNode: TDE软件节点指令配置参数
*                enSubmType: 当前节点的提交类型
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_S32      TdeOsiListAddNode(TDE_HANDLE s32Handle, TDE_NODE_BUF_S* pSwNode,
                              TDE_NODE_SUBM_TYPE_E enSubmType, HI_U32 u32PhyBuffNumInNode);

/*****************************************************************************
* Function:      TdeOsiListSubmitJob
* Description:   创建链表,返回链表头指针
* Input:         s32Handle: 需要提交的Job的头节点指针
*                enListType: 提交的操作加入到Aq还是Sq中
*                bBlock: 是否阻塞
*                u32TimeOut: 超时时间
*                pFuncComplCB: 完成操作回调函数
* Output:        无
* Return:        成功/失败/超时
* Others:        无
*****************************************************************************/
HI_S32      TdeOsiListSubmitJob(TDE_HANDLE s32Handle, TDE_LIST_TYPE_E enListType,
                                HI_U32 u32TimeOut, TDE_FUNC_CB pFuncComplCB, HI_VOID *pFuncPara,
                                TDE_NOTIFY_MODE_E enNotiType);

/*****************************************************************************
 Prototype    : TdeOsiListReset
 Description  : Reset所有状态,释放链表空间
 Input        : 无
 Output       : NONE
 Return Value : HI_SUCCESS/HI_FAILURE
 Calls        :
 Called By    :
*****************************************************************************/
HI_VOID TdeOsiListReset(HI_VOID);

#if 0
/*****************************************************************************
* Function:      TdeOsiNodeComp
* Description:
* Input:         TDE_LIST_TYPE_E enListType
* Output:        无
* Return:        创建的任务句柄
* Others:        无
*****************************************************************************/
HI_VOID     TdeOsiListNodeComp(TDE_LIST_TYPE_E enListType);
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _TDE_OSILIST_H_ */
