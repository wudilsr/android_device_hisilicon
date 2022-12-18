/**
* @file sre_swi.ph
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ���������ж�ģ����ڲ�����ͷ�ļ��� \n
*/

#ifndef _SRE_SWI_PH
#define _SRE_SWI_PH

#include "sre_base.h"
#include "sre_swi.h"
#include "sre_list.ph"
#include "sre_sys.ph"
#include "sre_sys.h"
#include "sre_task.h"
#include "sre_err.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define SWI_INVALID_IDX    0xFFFF

#define SWI_MIN_CFG_NUM                0                         /*���ж������������С����*/
#define SWI_MAX_CFG_NUM                125                       /*���ж����������������*/

#define GET_SWI_OBJLIST(ptr)           LIST_COMPONENT(ptr, SWI_ATTRIBUTE_S, stObjList)

#define CHECK_SWI_ID(uwSwiID)          ((uwSwiID - OS_SYS_PID_BASE) >= g_usSwiMaxNum)

#define SWI_GET_INDEX(uwSwiID)          ((uwSwiID) & 0x000000FF)

#define GET_SCB_HANDLE(SwiPID)      ((SWI_ATTRIBUTE_S *)&(g_stSwiData.pstList[GET_HANDLE(SwiPID)]))

/*�ж��Ƿ񴴽��ж�����ж�*/
#define CHECK_SWI_MULTI(usPrio)         (g_aucSwiNum[usPrio] > 1)

/*���ж����ȼ���BIT����*/
#define SWI_PRIO_MASK(usPrio)           ((UINT32)0x80000000 >> (usPrio))

/*�������жϾ���λ,����Ϊ���ж����ȼ���BIT����*/
#define SET_SWI_READY(uwPrioMask)       (g_vuwSwiRdy |= (uwPrioMask))

/*������жϾ���λ,����Ϊ���ж����ȼ���BIT����*/
#define CLR_SWI_READY(uwPrioMask)       (g_vuwSwiRdy &= ~(uwPrioMask))

//#define OS_TRACE_SWI_DEL(uwSwiPid)\
//    ((NULL == g_pfnTraceSwiDel) ? ((VOID)0) : (VOID)g_pfnTraceSwiDel(uwSwiPid))

//typedef UINT32 (*OS_MCSWI_ACTIVE_FUNC) (UINT32, UINT8, UINT32);
typedef UINT32 (*OS_SWI_ACTIVE_FUNC)   (UINT32);
typedef UINT32 (* SWI_NAMEADD_FUNC)    (UINT32 uwSwiID, CHAR* pcName);
typedef VOID   (* SWI_NAMEDEL_FUNC)    (UINT32 uwSwiID);
//typedef UINT32 (* TRACE_INT_DELETE)    (UINT32);
typedef VOID   (* SWI_CORESLEEP_FUNC)  (VOID);

/**
* ���ж����ԵĽṹ�嶨�塣
*
* pfnHandler-->uwInitValue��λ�ò��ܱ䶯���������д�����ṹ��СҲ�̶���
* uwRealValue��uwLockValue��λ�ò��ܱ䶯���������д������uwRealValue�ĵ�ַ
   ��8�ı�����
* Attention: for performance, the size of SWI_ATTRIBUTE_S must be multiple of 8
*/
typedef struct tagSwiAttribute
{
    SWI_PROC_FUNC pfnHandler;           /* ���жϴ�����           */
    SWI_STATUS_T  usStatus;             /* ���ж�״̬               */
    SWI_PRIOR_T   usPriority;           /* ���ж����ȼ�             */
    UINT32        uwRealValue;          /* ���ж�ʵʱֵ             */
    UINT32        uwLockValue;          /* ���жϴ���ʱ������ֵ     */
    UINT32        uwInitValue;          /* ���жϴ���ʱ�ĳ�ʼֵ     */
    UINT32        uwNumOfMsg;           /* ���ж�δ���յ���Ϣ��     */
    LIST_OBJECT_S stMsgList;            /* ���ж���Ϣ�б�           */
    /* ���ж�δ����ʱstObjList����FreeList������δ����ʱΪNULL�����������ReadyList */
    LIST_OBJECT_S stObjList;
    /* ���жϴ�������,ֻ�и��ڸ����ȼ����������ȼ������жϲ�����ռ */
    SWI_PRIOR_T   usPriLevel;
    UINT16        usReserved;
    UINT32        uwSwiPid;
#if  (OS_HAVE_COPROCESSOR1 == YES) /*������Tensilica*/
    VOID         *pCpSaveAreaA;         /* point to context buffer A of coprocessor1 */
    VOID         *pCpSaveAreaB;         /* point to context buffer B of coprocessor1 */
#endif
} SWI_ATTRIBUTE_S;

typedef struct tagSwiList
{
    SWI_ATTRIBUTE_S *pstList;
} SWI_LIST_S;

extern SWI_LIST_S                g_stSwiData;      /* ָ�����жϿ��ƿ����� */
extern UINT32                    g_vuwSwiRdy;      /* ���жϾ������У�λ��������������ӦλΪ1 */
extern SWI_ATTRIBUTE_S          *g_pstSwiActive;   /* �����жϴ���ʱ��ָ��ǰ��������ж� */
//extern OS_MCSWI_ACTIVE_FUNC      g_pfnMcSwiActive;
extern LIST_OBJECT_S             g_astSwiReadyList[OS_SWI_PRIORITY_ALL];
extern SWI_HANDLE_T              g_uwIdleSwiID;
extern UINT8                     g_aucSwiNum[OS_SWI_PRIORITY_ALL];
extern SWI_PRIOR_T               g_usSwiPriorityLevel;
//extern TRACE_INT_DELETE          g_pfnTraceSwiDel;
extern SWI_NAMEADD_FUNC          g_pfnSwiNameAdd;
extern SWI_NAMEDEL_FUNC          g_pfnSwiNameDel;
extern UINT16                    g_usSwiMaxNum;        /* ����ʹ�õ����ж����� */

extern SWI_PROC_FUNC        g_pfnSwiIdleEntry;

//extern UINT32 osMcSwiActNullHandler(UINT32 uwDstPid, UINT8 ucOprtType, UINT32 uwOprtNum);

extern SWI_ATTRIBUTE_S* osSwiRdyPop(UINT16 usPriority);

/*****************************************************************************
 Description : ���Ӿ������ж�
 Input       : pSwiCB     --- ���жϵĿ��ƿ�.
               usPrio     --- ���жϵ����ȼ�
 Output      : ��
 Return      : ��
 Others      : ����pSwiCB�����ȼ��ǳ��ڼ������ж�ʱ���ܵĿ��ǣ��ڸ�����SRE_SwiActivate�У�
 pSwiCB�����ȼ���֪��û��Ҫ��osSwiReadyAdd�ٻ�ȡһ��pSwiCB�����ȼ���osSwiReadyDel����ͬ��
 *****************************************************************************/
OS_SEC_ALW_INLINE INLINE VOID osSwiReadyAdd(SWI_ATTRIBUTE_S *pstSwiCB, UINT16 usSwiPrio)
{
    LIST_OBJECT_S   *pstReadyList;

    if (CHECK_SWI_MULTI(usSwiPrio))
    {
        if (OS_SWI_READY & pstSwiCB->usStatus)
        {
            /* ��ֹ�ظ�����������Ŷӵ�Ready��β������Ready���й������ظ�����޴����⡣*/
            return;
        }

        /*�����ж�����ж�,���۾��������ж��Ƿ��ж��,�������������*/
        pstReadyList = &(g_astSwiReadyList[usSwiPrio]);
        ListTailAdd(&(pstSwiCB->stObjList), pstReadyList);
    }
    else
    {
        /*ֻ��һ�����ж�,ǰ�洴��ʱ,�Ѿ���pstPrevָ����SCB,��ʱ,ֱ���þ���λ�Ϳ�����*/
    }

    SET_SWI_READY(SWI_PRIO_MASK(usSwiPrio)); //�����жϾ���λ
    pstSwiCB->usStatus |= OS_SWI_READY;
    g_vuwUniFlag     |= OS_FLG_SWI_REQ;
}

/*****************************************************************************
 Description : ɾ�����������ж�
 Input       : pSwiCB     --- �������жϵĿ��ƿ�.
               usPrio     --- �������жϵ����ȼ�
 Output      : ��
 Return      : ��
 *****************************************************************************/
OS_SEC_ALW_INLINE INLINE VOID osSwiReadyDel(SWI_ATTRIBUTE_S *pstSwiCB, UINT16 usPrio)
{
    LIST_OBJECT_S   *pstReadyList;
    UINT32          uwPrioMask;

    uwPrioMask = SWI_PRIO_MASK(usPrio);
    if (CHECK_SWI_MULTI(usPrio))
    {
        /*�����ж�����жϣ������ȼ��ľ���������ɾ��*/
        pstReadyList = &(g_astSwiReadyList[usPrio]);
        ListDelete(&pstSwiCB->stObjList);
        if (ListEmpty(pstReadyList))
        {
            CLR_SWI_READY(uwPrioMask);     //������ȼ��ľ���λ
        }
    }
    else
    {
        CLR_SWI_READY(uwPrioMask);        //������ȼ��ľ���λ
    }

    pstSwiCB->usStatus &= ~OS_SWI_READY;    //������жϵľ���̬
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_SWI_PH */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

