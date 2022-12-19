/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_drv_api.c
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
#include "hi_jpeg_drv_api.h"


#ifdef CONFIG_JPEG_OMX_FUNCTION

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API forward declarations *******************/

/******************************* API realization *****************************/
/***************************************************************************
* func          : HI_DRV_JPEG_Open
* description   : open jpeg dev.
                  CNcomment: ��jpeg�豸 CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 HI_DRV_JPEG_Open(HI_VOID)
{
    return HI_SUCCESS;
}

/***************************************************************************
* func          : HI_DRV_JPEG_Close
* description   : close jpeg dev.
                  CNcomment: �ر�jpeg�豸 CNend\n
* others:       : NA
****************************************************************************/
HI_VOID HI_DRV_JPEG_Close(HI_VOID)
{
}

/***************************************************************************
* func          : HI_DRV_JPEG_CreateDec
* description   : ctreate jpeg decoder.
                  CNcomment: ���������� CNend\n
* param[in]     : *pu32Handle
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 HI_DRV_JPEG_CreateDec(HI_U32 *pu32Handle)
{
    return HI_SUCCESS;
}


#ifdef CONFIG_JPEG_MMU_SUPPORT
/***************************************************************************
* func          : HI_DRV_JPEG_SetDecMemType
* description   : ���ý������ڴ�ʹ������.
                  CNcomment: ���������� CNend\n
* param[in]     : u32Handle
* param[in]     : u32MemTypeMask
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 HI_DRV_JPEG_SetDecMemType(HI_U32 u32Handle,HI_U32 u32MemTypeMask)
{
	return HI_SUCCESS;
}
#endif


/***************************************************************************
* func          : HI_DRV_JPEG_DecInfo
* description   : get jpeg input infomation.
                  CNcomment: ��ȡͼƬ������Ϣ CNend\n
* param[in]     : u32Handle
* param[in]     : *stInMsg
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 HI_DRV_JPEG_DecInfo(HI_U32 u32Handle,HI_DRV_JPEG_INMSG_S *stInMsg)
{
    return HI_SUCCESS;
}

/***************************************************************************
* func          : HI_DRV_JPEG_DecOutInfo
* description   : get jpeg output infomation.
                  CNcomment: ��ȡͼƬ�����Ϣ CNend\n
* param[in]     : u32Handle
* param[in]     : *stOutMsg
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 HI_DRV_JPEG_DecOutInfo(HI_U32 u32Handle,HI_DRV_JPEG_OUTMSG_S *stOutMsg)
{
    return HI_SUCCESS;
}

/***************************************************************************
* func          : HI_DRV_JPEG_DecFrame
* description   : dec one frame.
                 CNcomment: ����һ֡ͼƬ CNend\n
* param[in]     : u32Handle
* param[in]     : *stInMsg
* param[in]     : *stOutMsg
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 HI_DRV_JPEG_DecFrame(HI_U32 u32Handle,HI_DRV_JPEG_INMSG_S *stInMsg,HI_DRV_JPEG_OUTMSG_S *stOutMsg)
{
    return HI_SUCCESS;
}

/***************************************************************************
* func          : HI_DRV_JPEG_DestoryDec
* description   : destory decode.
                  CNcomment: ���ٽ����� CNend\n
* param[in]     : u32Handle
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 HI_DRV_JPEG_DestoryDec(HI_U32 u32Handle)
{
    return HI_SUCCESS;
}

/***************************************************************************************
* func			: HI_DRV_JPEG_GetLuPixSum
* description	: get lu pix sum
				  CNcomment: ��ȡ����ֵ�� CNend\n
* param[in] 	: u32Handle
* retval		: HI_SUCCESS
* retval		: HI_FAILURE
* others:		: NA
***************************************************************************************/
HI_VOID HI_DRV_JPEG_GetLuPixSum(HI_U32 u32Handle,HI_U64* pu64LuPixValue)
{
	return;
}

EXPORT_SYMBOL(HI_DRV_JPEG_Open);
EXPORT_SYMBOL(HI_DRV_JPEG_Close);
EXPORT_SYMBOL(HI_DRV_JPEG_CreateDec);
EXPORT_SYMBOL(HI_DRV_JPEG_DecOutInfo);
EXPORT_SYMBOL(HI_DRV_JPEG_DecFrame);
EXPORT_SYMBOL(HI_DRV_JPEG_DestoryDec);
EXPORT_SYMBOL(HI_DRV_JPEG_GetLuPixSum);
#endif
