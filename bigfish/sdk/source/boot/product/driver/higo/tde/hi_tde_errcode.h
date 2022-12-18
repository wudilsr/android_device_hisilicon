/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hi_tde_errcode.h
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         : 
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y00181162                Created file        
******************************************************************************/

#ifndef __HI_TDE_ERRCODE_H__
#define __HI_TDE_ERRCODE_H__


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
#define HI_ERR_TDE_BASE  ((HI_S32)( ((0x80UL + 0x20UL)<<24) | (100 << 16 ) | (4 << 13) | 1 ))

enum 
{
    HI_ERR_TDE_DEV_NOT_OPEN = HI_ERR_TDE_BASE,  /**<  tde device not open yet */ 
    HI_ERR_TDE_DEV_OPEN_FAILED,                 /**<  open tde device failed */
    HI_ERR_TDE_NULL_PTR,                        /**<  input parameters contain null ptr */
    HI_ERR_TDE_NO_MEM,                          /**<  malloc failed  */
    HI_ERR_TDE_INVALID_HANDLE,                  /**<  invalid job handle */
    HI_ERR_TDE_INVALID_PARA,                    /**<  invalid parameter */
    HI_ERR_TDE_NOT_ALIGNED,                     /**<  aligned error for position, stride, width */
    HI_ERR_TDE_MINIFICATION,                    /**<  invalid minification */
    HI_ERR_TDE_CLIP_AREA,                       /**<  clip area and operation area have no intersection */
    HI_ERR_TDE_JOB_TIMEOUT,                     /**<  blocked job wait timeout */
    HI_ERR_TDE_UNSUPPORTED_OPERATION,           /**<  unsupported operation */
    HI_ERR_TDE_QUERY_TIMEOUT,                    /**<  query time out */
    HI_ERR_TDE_INTERRUPT              /* blocked job was interrupted */
};


/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/


#ifdef __cplusplus
					   
#if __cplusplus
					   
}

#endif
#endif /* __cplusplus */
					   
#endif /* __HI_TDE_ERRCODE_H__ */
