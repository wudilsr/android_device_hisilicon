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

/* �������ڵ����ݽṹ */
typedef struct hiTDE_SWNODE_S
{
    struct list_head stList;    
    HI_S32 s32Handle;           /* ���������ڵ�job���*/
    HI_S32 s32Index;            /* ��������job�е���ţ���1��ʼ��ţ������ͬ����ͬһ������ */
    TDE_NODE_SUBM_TYPE_E enSubmType; /* ��ǰ�ڵ����� */
    TDE_NOTIFY_MODE_E enNotiType;   /* �ڵ���ɺ��֪ͨ���� */
    TDE_NODE_BUF_S stNodeBuf;       /* ����������Ϣ�ڵ� */
    HI_U32 u32PhyBuffNum;           /* �����������buffer���� */
    struct hiTDE_SWNODE_S *pstParentNodeInCmd;/* ������ĵ�һ������ڵ� */
} TDE_SWNODE_S;

/* job���� */
typedef struct hiTDE_SWJOB_S
{
    struct list_head stList;    
    HI_S32 s32Handle;               /* job��� */
    TDE_FUNC_CB       pFuncComplCB; /* �ص�����ָ�� */
    HI_VOID * pFuncPara;            /* �ص��������� */
    TDE_NOTIFY_MODE_E enNotiType;   /* �ڵ���ɺ��֪ͨ���� */
    HI_U32 u32CmdNum;               /* job�к��е������� */
    HI_U32 u32NodeNum;              /* job�к��еĽڵ��� */
    TDE_SWNODE_S *pstFirstCmd;      /* job�еĵ�һ���������ڵ�����ڵ� */
    TDE_SWNODE_S *pstLastCmd;       /* job�е����һ���������ڵ�����ڵ� */
    TDE_SWNODE_S *pstTailNode;      /* job�е����һ������ڵ� */
    HI_BOOL bInQuery;               /* �Ƿ����û��ڲ�ѯ */
    HI_BOOL bSubmitted;             /* �Ƿ��Ѿ��ύ */
    HI_BOOL bAqUseBuff;             /* �Ƿ�ʹ����ʱbuffer*/
    TDE_SWNODE_S *pstParentCmd;     /*������¼���ڵ�*/
}TDE_SWJOB_S;

/****************************************************************************/
/*                             TDE osi list functions define                */
/****************************************************************************/

/*****************************************************************************
* Function:      TdeOsiSuspListInit
* Description:   ��ʼ������ڲ����ڻ���TDE������ȫ������
* Input:         null
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_S32      TdeOsiListInit(HI_VOID);

/*****************************************************************************
* Function:      TdeOsiListTerm
* Description:   �ͷ�����ڲ����ڻ���TDE������ȫ������
* Input:         NULL
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_VOID     TdeOsiListTerm(HI_VOID);

/*****************************************************************************
* Function:      TdeOsiListBeginJob
* Description:   ��������,��������ͷָ��
* Input:         ��
* Output:        ��
* Return:        ������������
* Others:        ��
*****************************************************************************/
HI_S32      TdeOsiListBeginJob(TDE_HANDLE *pHandle );

/*****************************************************************************
* Function:      TdeOsiListCancelJob
* Description:   ɾ��s32Handleָ��������
* Input:         s32Handle:��ɾ��������
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_S32      TdeOsiListCancelJob(TDE_HANDLE s32Handle);

/*****************************************************************************
* Function:      TdeOsiListAddNode
* Description:   ��������,��������ͷָ��
* Input:         s32Handle: ��Ҫ������Job��ͷ�ڵ�ָ��
*                pSwNode: TDE����ڵ�ָ�����ò���
*                enSubmType: ��ǰ�ڵ���ύ����
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_S32      TdeOsiListAddNode(TDE_HANDLE s32Handle, TDE_NODE_BUF_S* pSwNode,
                              TDE_NODE_SUBM_TYPE_E enSubmType, HI_U32 u32PhyBuffNumInNode);

/*****************************************************************************
* Function:      TdeOsiListSubmitJob
* Description:   ��������,��������ͷָ��
* Input:         s32Handle: ��Ҫ�ύ��Job��ͷ�ڵ�ָ��
*                enListType: �ύ�Ĳ������뵽Aq����Sq��
*                bBlock: �Ƿ�����
*                u32TimeOut: ��ʱʱ��
*                pFuncComplCB: ��ɲ����ص�����
* Output:        ��
* Return:        �ɹ�/ʧ��/��ʱ
* Others:        ��
*****************************************************************************/
HI_S32      TdeOsiListSubmitJob(TDE_HANDLE s32Handle, TDE_LIST_TYPE_E enListType,
                                HI_U32 u32TimeOut, TDE_FUNC_CB pFuncComplCB, HI_VOID *pFuncPara,
                                TDE_NOTIFY_MODE_E enNotiType);

/*****************************************************************************
 Prototype    : TdeOsiListReset
 Description  : Reset����״̬,�ͷ�����ռ�
 Input        : ��
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
* Output:        ��
* Return:        ������������
* Others:        ��
*****************************************************************************/
HI_VOID     TdeOsiListNodeComp(TDE_LIST_TYPE_E enListType);
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _TDE_OSILIST_H_ */
