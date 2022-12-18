/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : higo_io.h
Version             : Initial Draft
Author              : 
Created             : 2015/06/15
Description         : 输入处理
Function List       : 
History             :
Date                       Author                   Modification
2015/06/15                y00181162                Created file        
******************************************************************************/

#ifndef __HIGO_IO_H__
#define __HIGO_IO_H__


/*********************************add include here******************************/
#include "hi_type.h"
#include "hi_go_comm.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/

typedef enum
{
    IO_POS_SET = 0,
    IO_POS_CUR,
    IO_POS_END,
    IO_POS_BUTT
} IO_POS_E;


typedef struct hiIO_INSTANCE_S
{
	HI_CHAR *pAddr;        /**< pointer to memory                     **/
    HI_U32  u32Position;   /**< IO position , offset from file start  **/
    HI_U32  u32Length;     /**< length                                **/
}IO_INSTANCE_S;

/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/

/***************************************************************************************
* func          : HIGO_ADP_IOCreate
* description   : CNcomment: 创建码流处理句柄 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IOCreate(IO_INSTANCE_S* const pstStream, HI_CHAR* pStremBuf, HI_U32 u32StreamLen);

/***************************************************************************************
* func          : HIGO_ADP_IODestroy
* description   : CNcomment: 销毁码流处理句柄 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IODestroy(IO_INSTANCE_S* const pstStream);

/***************************************************************************************
* func          : HIGO_ADP_IORead
* description   : CNcomment: 读码流 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IORead(IO_INSTANCE_S* const pstStream, HI_VOID *pBuf, HI_U32 BufLen, HI_U32 *pCopyLen, HI_BOOL *pEndFlag);


/***************************************************************************************
* func          : HIGO_ADP_IOSeek
* description   : CNcomment: 码流回退的位置 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IOSeek(IO_INSTANCE_S* const pstStream, IO_POS_E Position, HI_U32 Offset);


/***************************************************************************************
* func          : HIGO_ADP_IOGetLength
* description   : CNcomment: 获取码流长度 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IOGetLength(IO_INSTANCE_S stStream, HI_U32 *pLength);


/***************************************************************************************
* func          : HIGO_ADP_IOGetPos
* description   : CNcomment: 获取码流位置 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIGO_ADP_IOGetPos(IO_INSTANCE_S stStream, HI_U32 *pPos);


#ifdef __cplusplus
}
#endif
#endif /* __HIGO_IO_H__ */
