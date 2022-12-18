/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : tde_handle.h
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         : 
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y00181162                Created file        
******************************************************************************/

#ifndef __TDE_HANDLE_H__
#define __TDE_HANDLE_H__


/*********************************add include here******************************/

#include "tde_define.h"
#include "list.h"

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/


typedef struct hiHandleMgr
{
    struct list_head stHeader;  /* ������֯handle */
    HI_S32   handle;
    HI_VOID *res;
} HI_HANDLE_MGR;

STATIC HI_HANDLE_MGR *s_pstTdeHandleList = NULL; /* ȫ��handle�����������*/

STATIC HI_S32 s_handle = 1; /* handle=0Ԥ�� */
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



/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/


STATIC HI_BOOL  initial_handle(HI_VOID)
{
    if (NULL == s_pstTdeHandleList)
    {
        s_pstTdeHandleList = (HI_HANDLE_MGR *) TDE_MALLOC(sizeof(HI_HANDLE_MGR));
        if (NULL == s_pstTdeHandleList)
        {
            return HI_FALSE;
        }

        /* ��ʼ������ͷ�� */
        INIT_LIST_HEAD(&s_pstTdeHandleList->stHeader);

    }

    s_handle = 1;

    return HI_TRUE;
}
        

STATIC HI_S32  get_handle(HI_HANDLE_MGR *res, HI_S32 *handle)
{
    TDE_HANDLE_SAFE_INC_NUM();
    list_add_tail(&res->stHeader, &s_pstTdeHandleList->stHeader);

    /* �����Ƿ�handle*/
    if (TDE_MAX_HANDLE_VALUE == s_handle)
    {
        s_handle = 1;
    }

    res->handle = s_handle;

    *handle = s_handle++;

    return 0;
}

/* Ϊ�˼ӿ�����ٶȣ��Ӻ���ǰ���� */
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
    /* �ͷ�ͷ�ڵ㣬ע��:�����ڵ㶼�ǹ������ģ�������Դ���ͷ��ɷ������ǵ�ģ�鸺�� */
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
#endif /* __cplusplus */

#endif /* __TDE_HANDLE_H__ */
