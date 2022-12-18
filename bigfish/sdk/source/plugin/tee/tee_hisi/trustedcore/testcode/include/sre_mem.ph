/**
* @file sre_mem.ph
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：内存基本功能的内部头文件。 \n
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



#define OS_SLICE_MAXTYPE                      8              /*  内存块的类型总数。                              */
#define OS_SLICE_HEAD_MAGICWORD               0xBABABABA     /*  内存块的块控制头。                              */
#define OS_MAX_PT_NUM                         20

#define OS_MCMEM_CTRL_STATE_VALID             0xad5678da
#define OS_MCMEM_CTRL_STATE_INVALID           0xae1234ea

#define OS_MEM_IS_SHARE_PT(ucPtNo)            (m_astMemPtInfo[ucPtNo].bShared)
#define OS_MEM_IS_CACHE_PT(ucPtNo)            (m_astMemPtInfo[ucPtNo].bCachable)

#define MEM_ARITH_MCSTAFSC MEM_ARITH_MCBLOCK   /**< 共享静态FSC算法,MEM_ARITH_MCBLOCK不使用，共享静态FSC占用MEM_ARITH_MCBLOCK的内存控制块*/

/*pool算法统一的块控制头                            */
typedef struct tagSliceCtrlHead
{
    UINT32 uwHead;                              /* 魔术字                                     */
    struct tagSliceCtrlHead *pNextFree;         /* 空闲时，指向下一个空闲块                   */
    UINT8  ucPtNo;                              /* 分区号                                     */
    UINT8  ucType;                              /* 块类型                                     */
    UINT16 usOffset;                            /* 私有和共享POOL内存：标识该块内存使用状况   */
    UINT32 *uwAlignPad;                         /* 记录块控制头的地址                         */
} OS_MEM_SLICE_CTRL_HEAD_S;

/*FSC算法块控制头结构，注意各成员顺序是和其他算法保持一致偏移的，不能随便改动*/
typedef struct tagFscMemCtrl
{
    struct tagFscMemCtrl *pstNext;    //空闲时为下一个空闲块地址，被使用时为魔术字OS_FSC_MEM_USED_MAGIC
    UINT16 usSize;                    //块大小
    UINT16 usPrev;                    //若前面相邻的物理块空闲，则此字段记录前面空闲块大小，否则为OS_FSC_MEM_PREV_USED
    UINT8  ucPtNo;                    //分区号
    UINT8  ucBlkId;                   //在共享静态FSC算法中存放Block Id,其余算法保留
    UINT16 usUserSize;                //在共享静态FSC算法中存放用户要申请的内存大小,其余算法保留
    struct tagFscMemCtrl *pstPrev;    //空闲时为上一个控制块地址，被使用时记录块控制头地址，相当于原来的uwAlignPad
}OS_FSC_MEM_CTRL_S;

/*－－－－－－FuncsLib－－－－－－                  */
/*  创建一个内存分区                                */
typedef UINT32 (*MEM_PTCREATE_F)
(
    UINT8  ucPtNo,
    VOID  *pPtAddr,
    UINT32 uwPtSize
);
/*  申请一个内存块                                  */
typedef VOID* (*MEM_ALLOC_F)
(
    UINT32   uwMid,
    UINT8    ucPtNo,
    UINT32   uwSize,
    OS_MEM_ALIGN_E    ucAlignPow
);
/*  释放一个内存块                                  */
typedef UINT32 (*MEM_FREE_F)
(
    UINT32  uwMid,
    UINT8    cPtNo,
    OS_MEM_SLICE_CTRL_HEAD_S     *pstSHead,
    UINT32 *puwSize
);

typedef struct tagFuncsLibMem
{
    MEM_PTCREATE_F       pfnPtCreate;           /* 创建一个内存分区                           */
    MEM_ALLOC_F          pfnAlloc;              /* 申请一个内存块                             */
    MEM_FREE_F           pfnFree;               /* 释放一个内存块                             */
}MEM_ARITH_API_S;

/* 分区控制块信息                                   */
typedef struct tagMemPtInfo
{
    OS_MEM_ARITH_E     enArith;                 /* 分区使用的内存算法                         */
    VOID              *pPtAddr;                 /* 分区起始地址                               */
    VOID              *pPtCtrl;                 /* 对于共享算法，指向多核共享内存分区控制头内存起始地址，对于私有FSC，指向空闲链表头数组*/
    UINT32             uwPtSize;                /* 分区大小                                   */
    UINT32             uwSliceMaxSize;          /* 最大块大小                                 */
    UINT32             uwTotalSize;             /* 分区总内存大小                             */
    UINT32             uwFreeSize;              /* 分区可供使用的内存大小                     */
    UINT8              bInstalled;              /* 分区是否被使用                             */
    UINT8              bCachable;               /* 分区是否cache                              */
    UINT8              bShared;                 /* 分区是否为共享分区                         */
    UINT8              Reserved;
    UINT32             uwBitMap;                /* 私有FSC的空闲链表Bitmap                    */
    MEM_ALLOC_F        pfnAlloc;                /* 该分区申请内存接口                         */
    MEM_FREE_F         pfnFree;                 /* 该分区释放内存接口                         */
}MEM_PT_INFO_S;

/* 共享内存分区控制头结构体，在缺省共享静态FSC内存中分配空间 */
typedef struct tagShareMemPtCtrl
{
    UINT32                    uwState;                          /* 本分区控制块是否有效 */
    OS_MEM_ARITH_E            enArith;                          /* 分区对应的算法       */
    VOID                     *pPtCtrl;                          /* 分区对齐后的地址     */
    VOID                     *pPtAddr;                          /* 分区起始地址         */
    UINT32                    uwPtSize;                         /* 分区大小             */
    BOOL                      bCachable;                        /* 分区是否cache        */
    UINT16                    ausSliceSize[OS_SLICE_MAXTYPE];   /* 分区块大小           */
    UINT32                    uwSpinLockId;                     /* 共享互斥锁           */
    VOID                     *pFreeTop;                         /* Raw内存块起始地址    */
    OS_MEM_SLICE_CTRL_HEAD_S *pFreeHead[OS_SLICE_MAXTYPE];      /* 空闲内存块链表头     */
} MCMEM_MEM_PT_CTRL_S;

/* 共享FSC内存分区控制头结构体，在缺省共享静态FSC内存分区中分配空间
 * 成员顺序不能随便动，需要与MCMEM_MEM_PT_CTRL_S成员保持一致*/
typedef struct tagShareFscMemPtCtrl
{
    UINT32                    uwState;                          /* 本分区控制块是否有效 */
    OS_MEM_ARITH_E            enArith;                          /* 分区对应的算法       */
    VOID                     *pPtCtrl;                          /* 分区对齐后的地址     */
    VOID                     *pPtAddr;                          /* 分区起始地址         */
    UINT32                    uwPtSize;                         /* 分区大小             */
    BOOL                      bCachable;                        /* 分区是否cache        */
    UINT32                    uwSpinLockId;                     /* 共享互斥锁           */
    UINT32                    uwFreeSize;
    UINT32                    uwBitMap;
    OS_FSC_MEM_CTRL_S        *pstFscFreeHead;
    UINT32                    uwPeakSize;                       /* 用于计算该分区最大的使用量 */
} MCMEM_FSCMEM_PT_CTRL_S;

#define OS_MCMEM_MEM_PT_CTRL_SIZE   sizeof(MCMEM_MEM_PT_CTRL_S)                                          /* 动态共享内存分区控制头大小      */
#define OS_SHARE_MIN_PT_SIZE(par)   m_astMemPtInfo[par].uwSliceMaxSize    /* 动态共享内存最小值              */


/* 创建共享内存分区时，用于记录共享内存分区信息控制体 */
typedef struct tagMemPtCheck
{
    VOID                    *pPtCtrl;          /* 指向分区控制块位置                          */
} MEM_PT_CHECK_S;

EXTERN_FAR MEM_PT_CHECK_S *g_astMemPtCheck;   /* 指向分区块首指针  只针对多核使用  */


/* 分区控制块信息，分配在缺省的私有FSC内存中      */
EXTERN_FAR MEM_PT_INFO_S  *m_astMemPtInfo;
/* 记录分区中各种块类型对应的块的大小              */
EXTERN_FAR UINT16 (*m_ausSliceTypeToSize)[OS_SLICE_MAXTYPE];
/* 记录申请内存对应最合适的块内存类型              */
EXTERN_FAR UINT8 **m_aucSliceSizeToType;

/**************** EXTERN VARIABLES *******************/
/* 不同算法对应的API接口                           */
extern MEM_ARITH_API_S m_astMemArithAPI[MEM_ARITH_BUTT];

/*  内存块控制头长度                               */
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

