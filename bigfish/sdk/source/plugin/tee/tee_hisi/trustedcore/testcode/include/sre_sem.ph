/**
 * @file sre_sem.ph
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������ź���ģ���ڲ�ͷ�ļ��� \n
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
    UINT16           usSemStat;      /* �Ƿ�ʹ�� OS_SEM_UNUSED/OS_SEM_USED  */
    UINT16           usSemID;        /* �����ź���������                    */
    UINT32           uwSemCount;     /* �����ź�������ʱ�����ź�������      */
    LIST_OBJECT_S    stSemList;      /* �ҽ������ڸ��ź���������            */
}SEM_CB_S;

EXTERN_FAR SEM_CB_S *g_pstAllSem;        /* ָ������ź������ƿ�                */

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
