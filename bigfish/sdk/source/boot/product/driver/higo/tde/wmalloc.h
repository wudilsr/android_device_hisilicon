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
*Description: TDE�ڴ�س�ʼ��
*Input: ��
*Output: ��
*Return: �ɹ�/������
others: ��
*******************************************************************************/
HI_S32 wmeminit(HI_VOID);

/******************************************************************************
*Function: wmalloc
*Description: ���ڴ���������ڴ�
*Input: size ������ڴ��С
*Output: ָ���ڴ���ָ��
*Return: ��
others: ��
*******************************************************************************/
HI_VOID *wmalloc(HI_U32 size);

/******************************************************************************
*Function: wfree
*Description: �ͷ��ڴ�
*Input: ptr ָ���ڴ���ָ��
*Output: ��
*Return: �ɹ�/������
others: ��
*******************************************************************************/
HI_S32 wfree(HI_VOID *ptr);

/******************************************************************************
*Function: wmemterm
*Description: TDE�ڴ��ȥ��ʼ��
*Input: ��
*Output: ��
*Return: ��
others: ��
*******************************************************************************/
HI_VOID wmemterm(HI_VOID);

/******************************************************************************
*Function: wgetphy
*Description: ��ȡ�ڴ�������ַ
*Input: ptr ָ���ڴ��ָ��
*Output: �����ַ
*Return: ��
others: ��
*******************************************************************************/
HI_U32 wgetphy(HI_VOID *ptr);

/******************************************************************************
*Function: wgetphy
*Description: ��ȡ�ڴ�������ַ
*Input: phyaddr �����ַ
*Output: �����ַ
*Return: ��
others: ��
*******************************************************************************/
HI_VOID * wgetvrt(HI_U32 phyaddr);

/******************************************************************************
*Function: wgetphy
*Description: ��ȡ�ڴ��ʣ���Unit��Ԫ��
*Input: ��
*Output: ��
*Return: ʣ��ĵ�Ԫ��
others: ��
*******************************************************************************/
HI_U32 wgetfreenum(HI_VOID);


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __WMALLOC_H__ */
