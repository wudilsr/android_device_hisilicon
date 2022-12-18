/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tde_define.h
* Description:TDE types define for all module
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/

#ifndef _TDE_DEFINE_H_
#define _TDE_DEFINE_H_

#include "hi_type.h"
#include "wmalloc.h"
//#include "hi_common.h"
#include "exports.h"
#include "hi_common.h"
#include "hifb_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cplusplus */
#endif  /* __cplusplus */

/****************************************************************************/
/*                             TDE types define                             */
/****************************************************************************/
/* ���ظ�ʽ���� */
typedef enum hiTDE_COLORFMT_CATEGORY_E
{
    TDE_COLORFMT_CATEGORY_ARGB,
    TDE_COLORFMT_CATEGORY_CLUT,
    TDE_COLORFMT_CATEGORY_An,
    TDE_COLORFMT_CATEGORY_YCbCr,
    TDE_COLORFMT_CATEGORY_BYTE,
    TDE_COLORFMT_CATEGORY_HALFWORD,
    TDE_COLORFMT_CATEGORY_MB,
    TDE_COLORFMT_CATEGORY_BUTT
} TDE_COLORFMT_CATEGORY_E;


/* �ڵ���ύ����,�����Ĳ����ڵ�/����ͷ�ڵ�/�����м�ڵ� */
typedef enum hiTDE_NODE_SUBM_TYPE_E
{
    TDE_NODE_SUBM_ALONE = 0,    /*��ǰ�ڵ��ύΪ���������Ľڵ�*/
    TDE_NODE_SUBM_PARENT = 1,   /*��ǰ�ڵ��ύΪ�����ĸ��ڵ�*/
    TDE_NODE_SUBM_CHILD = 2    /*��ǰ�ڵ��ύΪ�������ӽڵ�*/
}TDE_NODE_SUBM_TYPE_E;

typedef enum hiTDE_BUFFER_USAGE_E
{
    TDE_BUFFER_USAGE_BITMAP = 0,
    TDE_BUFFER_USAGE_Y,
    TDE_BUFFER_USAGE_CbCr,
    TDE_BUFFER_USAGE_BUTT
} TDE_BUFFER_USAGE_E;

/* ���������,ͬ������(SQ)/�첽����(AQ) */
typedef enum hiTDE_LIST_TYPE_E
{
    TDE_LIST_AQ = 0,    /* �첽���� */
    TDE_LIST_SQ,        /* ͬ������ */
    TDE_LIST_BUTT
} TDE_LIST_TYPE_E;

/*����������Ϣ�ڵ�*/
typedef struct hiTDE_NODE_BUF_S
{
    HI_VOID *pBuf; /*������Ϣ�ڵ���buffer*/
    HI_U32   u32NodeSz;/*��ǰ�ڵ�ռ�õĿռ�,�ֽ�Ϊ��λ*/
    HI_U64   u64Update;/*��ǰ�ڵ�ĸ��±��*/
    HI_U32   u32PhyAddr;/*��ǰ�ڵ���Ӳ�������еĵ�ַ*/
} TDE_NODE_BUF_S;

/* ��ǰ�ڵ���ɺ��֪ͨģʽ */
typedef enum hiTDE_NOTIFY_MODE_E
{
    TDE_JOB_NONE_NOTIFY = 0,    /* �ڵ���ɺ�����֪ͨ */
    TDE_JOB_COMPL_NOTIFY,   /* �ڵ���ɺ�֪ͨ */
    TDE_JOB_WAKE_NOTIFY,    /* �ڵ���ɺ��ѵȴ� */
    TDE_JOB_NOTIFY_BUTT
} TDE_NOTIFY_MODE_E;

#if  defined(CHIP_TYPE_hi3720v100) || defined(CHIP_TYPE_hi3716hv100) || defined(CHIP_TYPE_hi3716cv100)  || defined (CHIP_TYPE_hi3716mv100)
#define TDE_VERSION_MPW
#elif defined(CHIP_TYPE_hi3720v101) || defined(CHIP_TYPE_hi3716hv101) || defined(CHIP_TYPE_hi3716cv101)  || defined(CHIP_TYPE_hi3716mv101)
#define TDE_VERSION_PILOT
#elif  defined(CHIP_TYPE_fpga)
#define TDE_VERSION_FPGA
#else
#define TDE_VERSION_PILOT
#endif

#define TDE_KERN_ERR    0
#define TDE_KERN_WARNING    1
#define TDE_KERN_INFO   2
#define TDE_KERN_DEBUG  3

#define TDE_TRACE_LEVEL TDE_KERN_ERR
#define TDE_CSC_ENABLE
#define STATIC static
#define INLINE inline
#define TDE_MAX_PROC_NUM 40
#define TDE_MAX_WAIT_TIMEOUT 2000
//#define TDE_PROC_ENABLE
//#define TDE_DEBUG

/* �ر�BOOT�꣬���ڷ�boot�����µ��ԣ���ʱ������MMZ*/
#define BOOT

#define TDE_ASSERT(expr)
#ifdef TDE_DEBUG
#define TDE_TRACE( level, fmt, args... ) do\
{\
    if (level <= TDE_TRACE_LEVEL)\
    {\
        printf("%s(): Line%d : "fmt, __FUNCTION__,  __LINE__ , ##args);\
    }\
}while(0)
#else
#define TDE_TRACE( level, fmt, args... )
#endif

#ifdef BOOT
#define TDE_REG_MAP(base, size) \
    (base)

#define TDE_REG_UNMAP(p)

#if 0
#define TDE_MEM_NEW(size, align, mmz_name,mmb_name) \
    (TDE_MEM_ADDR)
#else
#define TDE_MEM_NEW(addr,size, align, mmz_name,mmb_name) \
{\
    HI_S32 ret;  \
    ret = HI_MEM_Alloc(&addr, size); \
    if (ret != HI_SUCCESS) \
    { \
        Debug("TDE_MEM_NEW fail\n"); \
        return HI_FAILURE;\
    }\
}
#endif
#define TDE_MEM_FREE(phyaddr)


#define TDE_MEM_MAP(phyaddr, cached) \
    (phyaddr)

#define TDE_MEM_UNMAP(phyaddr)

#else
#define TDE_REG_MAP(base, size) \
    HI_MEM_Map(base, size)

#define TDE_REG_UNMAP(p) \
    HI_MEM_Unmap(p)

#define TDE_MEM_NEW(size, align, mmz_name,mmb_name) \
    HI_MMZ_New(size, align, mmz_name, mmb_name)

#define TDE_MEM_FREE(phyaddr) \
    HI_MMZ_Delete(phyaddr)

#define TDE_MEM_MAP(phyaddr, cached) \
    HI_MMZ_Map(phyaddr, cached)

#define TDE_MEM_UNMAP(phyaddr) \
    HI_MMZ_Unmap(phyaddr)
#endif

#ifdef TDE_PROC_ENABLE
    extern HI_U32 g_u32TdeMallocCnt;
#endif

STATIC INLINE HI_VOID * TDE_MALLOC(HI_U32 size)
{
    HI_VOID* ptr;

#ifdef TDE_PROC_ENABLE
    g_u32TdeMallocCnt++;
#endif

    ptr = (HI_VOID *)wmalloc(size);
    return ptr;

}

STATIC INLINE HI_VOID TDE_FREE(HI_VOID* ptr)
{
    wfree(ptr);

#ifdef TDE_PROC_ENABLE
        g_u32TdeMallocCnt--;
#endif
}

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _TDE_DEFINE_H_ */
