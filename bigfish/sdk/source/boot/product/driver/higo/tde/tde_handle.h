/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name             :   handle.h
  Version               :   Initial Draft
  Author                :   Hisilicon multimedia software group
  Created               :   2008/03/05
  Last Modified         :
  Description           :
  Function List         :
  History               :
  1.Date                :   2008/03/05
    Author              :   w54130
Modification            :   Created file
******************************************************************************/
#ifndef  __HI_HANDLE_MGR_H__
#define  __HI_HANDLE_MGR_H__

#include "tde_define.h"
#include "list.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

typedef struct hiHandleMgr
{
    struct list_head stHeader;  /* 用于组织handle */
    HI_S32   handle;
    HI_VOID *res;
} HI_HANDLE_MGR;

STATIC HI_HANDLE_MGR *s_pstTdeHandleList = NULL; /* 全局handle管理链表队列*/

STATIC HI_S32 s_handle = 1; /* handle=0预留 */
STATIC HI_S32 s_s32HandleNum = 0;

#define TDE_MAX_JOB_NUM 512
#define TDE_MAX_HANDLE_VALUE 0x7fffffff

#define TDE_HANDLE_SAFE_INC_NUM() \
    do{\
        if (s_s32HandleNum >= TDE_MAX_JOB_NUM)\
        {\
            return -1;\
        }\
        else\
        {\
            s_s32HandleNum++;\
        }\
    } while(0)

#define TDE_HANLE_SAFE_DEC_NUM()\
    do{\
        if (--s_s32HandleNum < 0)\
        {\
            s_s32HandleNum = 0;\
        }\
    }while(0)

#define TDE_IS_JOB_FULL() (s_s32HandleNum == TDE_MAX_JOB_NUM)
STATIC HI_BOOL  initial_handle(HI_VOID)
{
    if (NULL == s_pstTdeHandleList)
    {
        s_pstTdeHandleList = (HI_HANDLE_MGR *) TDE_MALLOC(sizeof(HI_HANDLE_MGR));
        if (NULL == s_pstTdeHandleList)
        {
            return HI_FALSE;
        }

        /* 初始化链表头部 */
        INIT_LIST_HEAD(&s_pstTdeHandleList->stHeader);

    }

    s_handle = 1;

    return HI_TRUE;
}
        

STATIC HI_S32  get_handle(HI_HANDLE_MGR *res, HI_S32 *handle)
{
    TDE_HANDLE_SAFE_INC_NUM();
    list_add_tail(&res->stHeader, &s_pstTdeHandleList->stHeader);

    /* 跳过非法handle*/
    if (TDE_MAX_HANDLE_VALUE == s_handle)
    {
        s_handle = 1;
    }

    res->handle = s_handle;

    *handle = s_handle++;

    return 0;
}

/* 为了加快查找速度，从后往前查找 */
STATIC HI_BOOL  query_handle(HI_S32 handle, HI_HANDLE_MGR **res)
{
    HI_HANDLE_MGR *pstHandle = list_entry(s_pstTdeHandleList->stHeader.prev, HI_HANDLE_MGR, stHeader);

    while (pstHandle != s_pstTdeHandleList)
    {
        if (pstHandle->handle == handle)
        {
            *res = pstHandle;
            return HI_TRUE;
        }

        pstHandle = list_entry(pstHandle->stHeader.prev, HI_HANDLE_MGR, stHeader);
    }

    return HI_FALSE;
}

STATIC HI_BOOL  release_handle(HI_S32 handle)
{
    HI_HANDLE_MGR *pstHandle = list_entry(s_pstTdeHandleList->stHeader.next, HI_HANDLE_MGR, stHeader);

    while (pstHandle != s_pstTdeHandleList)
    {
        if (pstHandle->handle == handle)
        {
            list_del_init(&pstHandle->stHeader);
            TDE_HANLE_SAFE_DEC_NUM();
            return HI_TRUE;
        }

        pstHandle = list_entry(pstHandle->stHeader.next, HI_HANDLE_MGR, stHeader);
    }

    return HI_FALSE;
}

STATIC HI_VOID destroy_handle(HI_VOID)
{
    /* 释放头节点，注意:其他节点都是挂上来的，他们资源的释放由分配他们的模块负责 */
    if (NULL != s_pstTdeHandleList)
    {
        TDE_FREE(s_pstTdeHandleList);
        s_pstTdeHandleList = NULL;
    }

    return;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* __HI_HANDLE_MGR_H__ */
