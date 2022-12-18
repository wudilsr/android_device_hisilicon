/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : wmalloc.h
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         : 
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y00181162                Created file        
******************************************************************************/

#ifndef __WMALLOC_H__
#define __WMALLOC_H__


/*********************************add include here******************************/

#include "hi_type.h"

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/




/******************************************************************************
*Function: wmeminit
*Description: TDE内存池初始化
*Input: 无
*Output: 无
*Return: 成功/错误码
others: 无
*******************************************************************************/
HI_S32 wmeminit(HI_VOID);

/******************************************************************************
*Function: wmalloc
*Description: 从内存池中申请内存
*Input: size 申请的内存大小
*Output: 指向内存块的指针
*Return: 无
others: 无
*******************************************************************************/
HI_VOID *wmalloc(HI_U32 size);

/******************************************************************************
*Function: wfree
*Description: 释放内存
*Input: ptr 指向内存块的指针
*Output: 无
*Return: 成功/错误码
others: 无
*******************************************************************************/
HI_S32 wfree(HI_VOID *ptr);

/******************************************************************************
*Function: wmemterm
*Description: TDE内存池去初始化
*Input: 无
*Output: 无
*Return: 无
others: 无
*******************************************************************************/
HI_VOID wmemterm(HI_VOID);

/******************************************************************************
*Function: wgetphy
*Description: 获取内存的物理地址
*Input: ptr 指向内存的指针
*Output: 物理地址
*Return: 无
others: 无
*******************************************************************************/
HI_U32 wgetphy(HI_VOID *ptr);

/******************************************************************************
*Function: wgetphy
*Description: 获取内存的虚拟地址
*Input: phyaddr 物理地址
*Output: 虚拟地址
*Return: 无
others: 无
*******************************************************************************/
HI_VOID * wgetvrt(HI_U32 phyaddr);

/******************************************************************************
*Function: wgetphy
*Description: 获取内存的剩余的Unit单元数
*Input: 无
*Output: 无
*Return: 剩余的单元数
others: 无
*******************************************************************************/
HI_U32 wgetfreenum(HI_VOID);


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __WMALLOC_H__ */
