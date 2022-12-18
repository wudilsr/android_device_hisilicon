/**
 * @file sre_hunt.ph
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������PID��ȡ�Ķ���ͷ�ļ����� \n
 */
#ifndef _SRE_HUNT_PH
#define _SRE_HUNT_PH

#include "sre_base.h"
#include "sre_hunt.h"
#include "sre_task.ph"
#include "sre_swi.ph"
#include "sre_list.ph"
#include "sre_err.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define THREAD_NUM  g_uwThreadNum

/* HUNTģ��Ŀ���ͷ */
typedef struct tagThreadRegS
{
    UINT32          uwThreadPID;
    CHAR            acName[OS_TSK_NAME_LEN];    /* Thread acName. */
}THREAD_IDX_S;

typedef struct tagThreadInfoS
{
    volatile UINT32 uwSpinLock;
    UINT8 ucMature;
    UINT8 ucSwiNum;
    UINT8 ucTskNum;
    UINT8 ucTotNum;
    THREAD_IDX_S * pstThreadLst;                /* ���˴���߳�������ʼ��ַ */
} THREADINFO_S;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif //_SRE_HUNT_PH

/*
 * History: \n
 * 2010-3-10, z00134877, Create this file. \n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */



