/**
 * @file sre_sem.ph
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：信号量模块内部头文件。 \n
 */

#ifndef _SRE_SEM_PH
#define _SRE_SEM_PH

#include "sre_base.h"
#include "sre_sem.h"
#include "sre_task.h"
#include "sre_list.ph"
#include "sre_err.ph"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define OS_SEM_UNUSED     0
#define OS_SEM_USED       1

#define       OS_SEM_COUNT_MAX   0xFFFFFFFE
#define GET_SEM_LIST(ptr)   LIST_COMPONENT(ptr, SEM_CB_S, stSemList)
#define GET_SEM(semid)      (((SEM_CB_S *)g_pstAllSem) + (semid))
#define       OS_MAX_PENDTASK_INFO 4

typedef struct
{
    UINT16           usSemStat;      /* 是否使用 OS_SEM_UNUSED/OS_SEM_USED  */
    UINT16           usSemID;        /* 核内信号量索引号                    */
    UINT32           uwSemCount;     /* 当该信号量已用时，其信号量计数      */
    LIST_OBJECT_S    stSemList;      /* 挂接阻塞于该信号量的任务            */
}SEM_CB_S;

EXTERN_FAR SEM_CB_S *g_pstAllSem;        /* 指向核内信号量控制块                */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _SRE_SEM_PH */

/*
 * History: \n
 * 2009-3-4, h00133330, Create this file. \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
