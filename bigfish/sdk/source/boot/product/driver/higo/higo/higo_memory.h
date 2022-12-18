/**
\file
\brief memory manager in boot
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2010-0513
\version draft
\author a
\date 2010-5-13
*/

#ifndef __ADP_BT_MEM_H__
#define __ADP_BT_MEM_H__

/* add include here */
#include "hi_type.h"
#include <malloc.h>
#include "malloc.h"
#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
#define HIGO_Malloc(size)       malloc(size)
#define HIGO_Free(pVirm)       free(pVirm) //(pVirm = pVirm)

#define HIGO_MMZ_Malloc(size)   HIGO_Malloc2(size)
#define HIGO_MMZ_Free(pVirm)    HIGO_Free2(pVirm)

/*************************** Structure Definition ****************************/


typedef struct _BT_FREE_S
{
	HI_U32 u32Size;
    struct _BT_FREE_S *pNext;
}BT_FREE_S;

/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/

HI_S32 HIGO_InitMemory(HI_VOID);

HI_VOID* HIGO_Malloc2(HI_U32 u32Size);

HI_VOID HIGO_Free2(HI_VOID* pAddr);

HI_VOID HIGO_DeInitMemory(HI_VOID);

BT_FREE_S* HIGO_GetFreeList(HI_VOID);
#ifdef __cplusplus
}
#endif
#endif /* __ADP_BT_MEM_H__ */
