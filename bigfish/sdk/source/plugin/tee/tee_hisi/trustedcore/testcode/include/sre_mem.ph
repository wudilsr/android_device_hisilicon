/**
* @file sre_mem.ph
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* �������ڴ�������ܵ��ڲ�ͷ�ļ��� \n
*/

#ifndef _SRE_MEM_PH
#define _SRE_MEM_PH

#include "sre_mem.h"
#include "sre_buildef.h"
#include "sre_hw.ph"
#include "sre_err.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */



#define OS_SLICE_MAXTYPE                      8              /*  �ڴ�������������                              */
#define OS_SLICE_HEAD_MAGICWORD               0xBABABABA     /*  �ڴ��Ŀ����ͷ��                              */
#define OS_MAX_PT_NUM                         20

#define OS_MCMEM_CTRL_STATE_VALID             0xad5678da
#define OS_MCMEM_CTRL_STATE_INVALID           0xae1234ea

#define OS_MEM_IS_SHARE_PT(ucPtNo)            (m_astMemPtInfo[ucPtNo].bShared)
#define OS_MEM_IS_CACHE_PT(ucPtNo)            (m_astMemPtInfo[ucPtNo].bCachable)

#define MEM_ARITH_MCSTAFSC MEM_ARITH_MCBLOCK   /**< ����̬FSC�㷨,MEM_ARITH_MCBLOCK��ʹ�ã�����̬FSCռ��MEM_ARITH_MCBLOCK���ڴ���ƿ�*/

/*pool�㷨ͳһ�Ŀ����ͷ                            */
typedef struct tagSliceCtrlHead
{
    UINT32 uwHead;                              /* ħ����                                     */
    struct tagSliceCtrlHead *pNextFree;         /* ����ʱ��ָ����һ�����п�                   */
    UINT8  ucPtNo;                              /* ������                                     */
    UINT8  ucType;                              /* ������                                     */
    UINT16 usOffset;                            /* ˽�к͹���POOL�ڴ棺��ʶ�ÿ��ڴ�ʹ��״��   */
    UINT32 *uwAlignPad;                         /* ��¼�����ͷ�ĵ�ַ                         */
} OS_MEM_SLICE_CTRL_HEAD_S;

/*FSC�㷨�����ͷ�ṹ��ע�����Ա˳���Ǻ������㷨����һ��ƫ�Ƶģ��������Ķ�*/
typedef struct tagFscMemCtrl
{
    struct tagFscMemCtrl *pstNext;    //����ʱΪ��һ�����п��ַ����ʹ��ʱΪħ����OS_FSC_MEM_USED_MAGIC
    UINT16 usSize;                    //���С
    UINT16 usPrev;                    //��ǰ�����ڵ��������У�����ֶμ�¼ǰ����п��С������ΪOS_FSC_MEM_PREV_USED
    UINT8  ucPtNo;                    //������
    UINT8  ucBlkId;                   //�ڹ���̬FSC�㷨�д��Block Id,�����㷨����
    UINT16 usUserSize;                //�ڹ���̬FSC�㷨�д���û�Ҫ������ڴ��С,�����㷨����
    struct tagFscMemCtrl *pstPrev;    //����ʱΪ��һ�����ƿ��ַ����ʹ��ʱ��¼�����ͷ��ַ���൱��ԭ����uwAlignPad
}OS_FSC_MEM_CTRL_S;

/*������������FuncsLib������������                  */
/*  ����һ���ڴ����                                */
typedef UINT32 (*MEM_PTCREATE_F)
(
    UINT8  ucPtNo,
    VOID  *pPtAddr,
    UINT32 uwPtSize
);
/*  ����һ���ڴ��                                  */
typedef VOID* (*MEM_ALLOC_F)
(
    UINT32   uwMid,
    UINT8    ucPtNo,
    UINT32   uwSize,
    OS_MEM_ALIGN_E    ucAlignPow
);
/*  �ͷ�һ���ڴ��                                  */
typedef UINT32 (*MEM_FREE_F)
(
    UINT32  uwMid,
    UINT8    cPtNo,
    OS_MEM_SLICE_CTRL_HEAD_S     *pstSHead,
    UINT32 *puwSize
);

typedef struct tagFuncsLibMem
{
    MEM_PTCREATE_F       pfnPtCreate;           /* ����һ���ڴ����                           */
    MEM_ALLOC_F          pfnAlloc;              /* ����һ���ڴ��                             */
    MEM_FREE_F           pfnFree;               /* �ͷ�һ���ڴ��                             */
}MEM_ARITH_API_S;

/* �������ƿ���Ϣ                                   */
typedef struct tagMemPtInfo
{
    OS_MEM_ARITH_E     enArith;                 /* ����ʹ�õ��ڴ��㷨                         */
    VOID              *pPtAddr;                 /* ������ʼ��ַ                               */
    VOID              *pPtCtrl;                 /* ���ڹ����㷨��ָ���˹����ڴ��������ͷ�ڴ���ʼ��ַ������˽��FSC��ָ���������ͷ����*/
    UINT32             uwPtSize;                /* ������С                                   */
    UINT32             uwSliceMaxSize;          /* �����С                                 */
    UINT32             uwTotalSize;             /* �������ڴ��С                             */
    UINT32             uwFreeSize;              /* �����ɹ�ʹ�õ��ڴ��С                     */
    UINT8              bInstalled;              /* �����Ƿ�ʹ��                             */
    UINT8              bCachable;               /* �����Ƿ�cache                              */
    UINT8              bShared;                 /* �����Ƿ�Ϊ�������                         */
    UINT8              Reserved;
    UINT32             uwBitMap;                /* ˽��FSC�Ŀ�������Bitmap                    */
    MEM_ALLOC_F        pfnAlloc;                /* �÷��������ڴ�ӿ�                         */
    MEM_FREE_F         pfnFree;                 /* �÷����ͷ��ڴ�ӿ�                         */
}MEM_PT_INFO_S;

/* �����ڴ��������ͷ�ṹ�壬��ȱʡ����̬FSC�ڴ��з���ռ� */
typedef struct tagShareMemPtCtrl
{
    UINT32                    uwState;                          /* ���������ƿ��Ƿ���Ч */
    OS_MEM_ARITH_E            enArith;                          /* ������Ӧ���㷨       */
    VOID                     *pPtCtrl;                          /* ���������ĵ�ַ     */
    VOID                     *pPtAddr;                          /* ������ʼ��ַ         */
    UINT32                    uwPtSize;                         /* ������С             */
    BOOL                      bCachable;                        /* �����Ƿ�cache        */
    UINT16                    ausSliceSize[OS_SLICE_MAXTYPE];   /* �������С           */
    UINT32                    uwSpinLockId;                     /* ��������           */
    VOID                     *pFreeTop;                         /* Raw�ڴ����ʼ��ַ    */
    OS_MEM_SLICE_CTRL_HEAD_S *pFreeHead[OS_SLICE_MAXTYPE];      /* �����ڴ������ͷ     */
} MCMEM_MEM_PT_CTRL_S;

/* ����FSC�ڴ��������ͷ�ṹ�壬��ȱʡ����̬FSC�ڴ�����з���ռ�
 * ��Ա˳������㶯����Ҫ��MCMEM_MEM_PT_CTRL_S��Ա����һ��*/
typedef struct tagShareFscMemPtCtrl
{
    UINT32                    uwState;                          /* ���������ƿ��Ƿ���Ч */
    OS_MEM_ARITH_E            enArith;                          /* ������Ӧ���㷨       */
    VOID                     *pPtCtrl;                          /* ���������ĵ�ַ     */
    VOID                     *pPtAddr;                          /* ������ʼ��ַ         */
    UINT32                    uwPtSize;                         /* ������С             */
    BOOL                      bCachable;                        /* �����Ƿ�cache        */
    UINT32                    uwSpinLockId;                     /* ��������           */
    UINT32                    uwFreeSize;
    UINT32                    uwBitMap;
    OS_FSC_MEM_CTRL_S        *pstFscFreeHead;
    UINT32                    uwPeakSize;                       /* ���ڼ���÷�������ʹ���� */
} MCMEM_FSCMEM_PT_CTRL_S;

#define OS_MCMEM_MEM_PT_CTRL_SIZE   sizeof(MCMEM_MEM_PT_CTRL_S)                                          /* ��̬�����ڴ��������ͷ��С      */
#define OS_SHARE_MIN_PT_SIZE(par)   m_astMemPtInfo[par].uwSliceMaxSize    /* ��̬�����ڴ���Сֵ              */


/* ���������ڴ����ʱ�����ڼ�¼�����ڴ������Ϣ������ */
typedef struct tagMemPtCheck
{
    VOID                    *pPtCtrl;          /* ָ��������ƿ�λ��                          */
} MEM_PT_CHECK_S;

EXTERN_FAR MEM_PT_CHECK_S *g_astMemPtCheck;   /* ָ���������ָ��  ֻ��Զ��ʹ��  */


/* �������ƿ���Ϣ��������ȱʡ��˽��FSC�ڴ���      */
EXTERN_FAR MEM_PT_INFO_S  *m_astMemPtInfo;
/* ��¼�����и��ֿ����Ͷ�Ӧ�Ŀ�Ĵ�С              */
EXTERN_FAR UINT16 (*m_ausSliceTypeToSize)[OS_SLICE_MAXTYPE];
/* ��¼�����ڴ��Ӧ����ʵĿ��ڴ�����              */
EXTERN_FAR UINT8 **m_aucSliceSizeToType;

/**************** EXTERN VARIABLES *******************/
/* ��ͬ�㷨��Ӧ��API�ӿ�                           */
extern MEM_ARITH_API_S m_astMemArithAPI[MEM_ARITH_BUTT];

/*  �ڴ�����ͷ����                               */
#define OS_SLICEHEAD_SIZE       sizeof(OS_MEM_SLICE_CTRL_HEAD_S)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* cpluscplus */
#endif /* cpluscplus */

#endif /* _SRE_MEM_PH */
/**
 * History:
 * 2009-1-20 a149045: Create this file.
 * 2009-9-11  z00134877: change this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

