/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : bmp_dec.h
Version             : Initial Draft
Author              : 
Created             : 2015/06/18
Description         : bmp解码
Function List       : 
History             :
Date                       Author                   Modification
2015/06/18                 y00181162                Created file        
******************************************************************************/

#ifndef __BMP_DEC_H__
#define __BMP_DEC_H__


/*********************************add include here******************************/
#include "hi_type.h"
#include "higo_common.h"
#include "higo_surface.h"
#include "higo_io.h"

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/

typedef HI_U32 BMP_HANDLE;

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/

/***************************************************************************************
* func          : BMP_CreateDecoder
* description   : CNcomment: 创建bmp解码器 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_CreateDecoder   (BMP_HANDLE *pBmpDec, const HIGO_DEC_ATTR_S *pSrcDesc);

/***************************************************************************************
* func          : BMP_DecImgData
* description   : CNcomment: 解图片数据，只支持0888 8888两种像素格式得
                             要是图片为0888得直接转成8888输出 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_DecImgData      (BMP_HANDLE  BmpDec,  HI_U32 Index, HIGO_SURFACE_S *pSurface);

/***************************************************************************************
* func          : BMP_DestroyDecoder
* description   : CNcomment: 销毁bmp解码器 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_DestroyDecoder  (BMP_HANDLE  BmpDec);

HI_S32 BMP_DecCommInfo     (BMP_HANDLE  BmpDec, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);
HI_S32 BMP_DecImgInfo      (BMP_HANDLE  BmpDec, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo);


#ifdef __cplusplus
					   
#if __cplusplus
					   
}

#endif
#endif /* __cplusplus */
					   
#endif /* __BMP_DEC_H__ */
