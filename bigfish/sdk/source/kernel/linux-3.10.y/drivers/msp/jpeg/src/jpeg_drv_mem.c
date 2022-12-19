/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_drv_mem.c
Version		    : Initial Draft
Author		    : 
Created		    : 2015/01/25
Description	    :
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2015/01/25		    y00181162  		    Created file      	
******************************************************************************/

/*********************************add include here******************************/

#include "hi_jpeg_config.h"
#include "jpeg_drv_parse.h"
#include "jpeg_drv_mem.h"

#ifdef CONFIG_JPEG_OMX_FUNCTION

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API forward declarations *******************/

/******************************* API realization *****************************/
/***************************************************************************************
* func			: jpeg_mem_alloc
* description	: alloc all memory
				  CNcomment: 分配所有内存 CNend\n
* param[in] 	: 
* others:		: NA
***************************************************************************************/
HI_S32 jpeg_mem_alloc(HI_S32 s32DecHandle)
{
    HI_U32 u32LayerSize = JPGD_DRV_STREAM_BUFFER;
    HI_CHAR* pDataVir   = NULL;
    HI_CHAR* pDataPhy   = 0;
    IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)s32DecHandle;

#ifdef CONFIG_JPEG_MMU_SUPPORT
	HI_BOOL bMemMMUType = HI_TRUE;
	pDataPhy = (HI_CHAR*)HI_GFX_AllocMemEx("JPEG_STREAM_BUF", "iommu", u32LayerSize, &bMemMMUType);
#else
    pDataPhy = (HI_CHAR*)HI_GFX_AllocMem("JPEG_STREAM_BUF",NULL,u32LayerSize);
#endif
	if(NULL == pDataPhy)
    {
        return HI_FAILURE;
    }

#ifdef CONFIG_JPEG_MMU_SUPPORT
    pDataVir = (HI_CHAR*)HI_GFX_MapCached((HI_U32)pDataPhy,u32LayerSize, bMemMMUType);
#else
	pDataVir = (HI_CHAR*)HI_GFX_MapCached((HI_U32)pDataPhy,u32LayerSize);
#endif
    if(NULL == pDataVir)
    {
	#ifdef CONFIG_JPEG_MMU_SUPPORT
        HI_GFX_FreeMem((HI_U32)pDataPhy, bMemMMUType);
	#else
        HI_GFX_FreeMem((HI_U32)pDataPhy);
	#endif
        return HI_FAILURE;
    }
    pstImgInfo->pStreamPhy  = pDataPhy;
    pstImgInfo->pStreamVir  = pDataVir;

#ifdef CONFIG_JPEG_MMU_SUPPORT
	if(HI_TRUE == bMemMMUType){
		pstImgInfo->u32MemTypeMask |= JPEG_DRV_STREAM_MEM_MMU_TYPE;
	}
#endif

    return HI_SUCCESS;
    
}

/***************************************************************************************
* func			: jpeg_mem_destory
* description	: destory all memory
				  CNcomment: 销毁所有内存 CNend\n
* param[in] 	: 
* others:		: NA
***************************************************************************************/
HI_VOID jpeg_mem_destory(HI_S32 s32DecHandle)
{
    IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)s32DecHandle;

    if (0 == s32DecHandle || NULL == pstImgInfo)
    {
        return;
    }
    if(NULL != pstImgInfo->pStreamVir)
    {
	#ifdef CONFIG_JPEG_MMU_SUPPORT
		HI_BOOL bMemMMUType = (pstImgInfo->u32MemTypeMask & JPEG_DRV_STREAM_MEM_MMU_TYPE)? HI_TRUE : HI_FALSE;
		HI_GFX_Unmap((HI_VOID*)pstImgInfo->pStreamVir, bMemMMUType);
	#else
        HI_GFX_Unmap((HI_VOID*)pstImgInfo->pStreamVir);
	#endif
        pstImgInfo->pStreamVir = NULL;
    }
    if(NULL != pstImgInfo->pStreamPhy)
    {
	#ifdef CONFIG_JPEG_MMU_SUPPORT
		HI_BOOL bMemMMUType = (pstImgInfo->u32MemTypeMask & JPEG_DRV_STREAM_MEM_MMU_TYPE)? HI_TRUE : HI_FALSE;
		HI_GFX_FreeMem((HI_U32)pstImgInfo->pStreamPhy, bMemMMUType);
	#else
        HI_GFX_FreeMem((HI_U32)pstImgInfo->pStreamPhy);
	#endif
        pstImgInfo->pStreamPhy = NULL;
    }
    
    HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)s32DecHandle);

}
#endif
