/**
 \file
 \brief HiGo图形库头文件
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author w66592
 \date 2008-5-13
 */

#ifndef __HI_GO_H__
#define __HI_GO_H__

/* add include here */
#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif
 HI_VOID HI_MMB_Init(HI_U32 uStartAddr , HI_U32 uLen);
 HI_S32 HI_MMB_DeInit( HI_VOID);
 HI_VOID *HI_MMB_New(HI_U32 size , HI_U32 align, HI_U8 *mmz_name, HI_U8 *mmb_name );
 HI_VOID *HI_MMB_Map(HI_U32 phys_addr, HI_U32 cached);
 HI_S32 HI_MMB_Unmap(HI_U32 phys_addr);
 HI_S32 HI_MMB_Delete(HI_U32 phys_addr);
 HI_S32 HI_MMB_Flush(HI_VOID);

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_H__ */
