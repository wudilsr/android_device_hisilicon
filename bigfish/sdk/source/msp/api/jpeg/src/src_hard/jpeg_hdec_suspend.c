/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_suspend.c
Version		    : Initial Draft
Author		    : y00181162
Created		    : 2014/06/20
Description	    : the suspend dispose
                  CNcomment: �������� CNend\n
                  ./sample_pmoc 0 ����ң��������
Function List 	:

			  		  
History       	:
Date				Author        		Modification
2014/06/20		    y00181162		    Created file      	
******************************************************************************/


/*********************************add include here******************************/
#include "jpeg_hdec_suspend.h"

#ifdef CONFIG_JPEG_SUSPEND

#include "jpeg_hdec_api.h"
#include "jpeg_hdec_rwreg.h"
#include "jpeg_hdec_adp.h"
#include "hi_jpeg_drv_api.h"
#include "hi_jpeg_reg.h"

/***************************** Macro Definition ******************************/

/******************** to see which include file we want to use***************/



/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/



/******************************* API forward declarations *******************/

/******************************* API realization *****************************/


/*****************************************************************************
* func			: JPEG_HDEC_GetSuspendSignal
* description	: get the suspend signal
				  CNcomment:  ��ȡ�����ź�             CNend\n
* param[in] 	: *pJpegHandle    CNcomment:  ���������   CNend\n
* param[in] 	: bSuspendSignal  CNcomment:  �����ź� CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_GetSuspendSignal(const JPEG_HDEC_HANDLE_S  *pJpegHandle,HI_BOOL *bSuspendSignal)
{


		HI_S32  s32RetVal = 0;
		HI_BOOL bSuspend  = HI_FALSE;
		s32RetVal = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_GETSUSPEND, &bSuspend);
		if(HI_SUCCESS != s32RetVal)
		{
			return;
		}
       
		*bSuspendSignal = bSuspend;

}

/*****************************************************************************
* func			: JPEG_HDEC_GetResumeSignal
* description	: get the resume signal
				  CNcomment:  ��ȡ���������ź�             CNend\n
* param[in] 	: *pJpegHandle    CNcomment:  ���������   CNend\n
* param[in] 	: bResumeSignal  CNcomment:   ���������ź� CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_GetResumeSignal(const JPEG_HDEC_HANDLE_S  *pJpegHandle,HI_BOOL *bResumeSignal)
{

		HI_S32  s32RetVal = 0;
		HI_BOOL bResume   = HI_FALSE;
		
		s32RetVal = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_GETRESUME, &bResume);
		if(HI_SUCCESS != s32RetVal)
		{
			return;
		}

		*bResumeSignal = bResume;

}

/*****************************************************************************
* func			: JPEG_HDEC_Resume
* description	: suspend resume
				  CNcomment: �������� CNend\n
* param[in] 	: cinfo       CNcomment:  �������         CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_Resume(const struct jpeg_decompress_struct *cinfo)
{


		HI_S32 s32RetVal = 0;
        HI_JPG_SAVEINFO_S stResumeValue;
		
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		memset(&stResumeValue,0,sizeof(HI_JPG_SAVEINFO_S));

#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE)
		s32RetVal = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
		if(HI_SUCCESS != s32RetVal)
		{
			 return;
		}
		//system("himd.l 0xFF300000");
#endif
		/**
		** cancel reset
		** CNcomment:������λ CNend\n
		**/
		s32RetVal = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_CANCEL_RESET);
		if(HI_SUCCESS != s32RetVal)
		{
			 return;
		}
		/**
		** waite cancel reset success
		** CNcomment:�ȴ�������λ�ɹ� CNend\n
		**/   
		//msleep(1); /** 1ms at least **/

		s32RetVal = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_GETRESUMEVALUE, &stResumeValue);
		if(HI_SUCCESS != s32RetVal)
		{
			return;
		}
        pJpegHandle->u32ResByteConsum = stResumeValue.u32ResByteConsu;

		s32RetVal = JPEG_HDEC_SetPara(cinfo);
		if(HI_SUCCESS != s32RetVal)
		{
			 return;
		}
		
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_BSRES_DATA0_CFG, (HI_S32)stResumeValue.u32ResumeData0);
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_BSRES_DATA1_CFG, (HI_S32)stResumeValue.u32ResumeData1);
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_BSRES_BIT_CFG,   (HI_S32)stResumeValue.u32ResBitRemain);
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_MCUY_CFG,        (HI_S32)stResumeValue.u32ResMcuy);
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PD_Y_CFG,        (HI_S32)stResumeValue.u32Pdy);
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PD_CBCR_CFG,     (HI_S32)stResumeValue.u32Pdcbcr);
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_DRI_CNT_CFG,     (HI_S32)stResumeValue.u32DriCnt);

#if 0
		JPEG_TRACE("===============================================================\n");
		JPEG_TRACE("pJpegHandle->u32ResByteConsum = %d\n",pJpegHandle->u32ResByteConsum);
		JPEG_TRACE("stResumeValue.u32ResumeData0  = %d\n",stResumeValue.u32ResumeData0);
		JPEG_TRACE("stResumeValue.u32ResumeData1  = %d\n",stResumeValue.u32ResumeData1);
		JPEG_TRACE("stResumeValue.u32ResBitRemain = %d\n",stResumeValue.u32ResBitRemain);
		JPEG_TRACE("stResumeValue.u32ResMcuy      = %d\n",stResumeValue.u32ResMcuy);
		JPEG_TRACE("stResumeValue.u32Pdy          = %d\n",stResumeValue.u32Pdy);
		JPEG_TRACE("stResumeValue.u32Pdcbcr       = %d\n",stResumeValue.u32Pdcbcr);
        JPEG_TRACE("stResumeValue.u32DriCnt       = %d\n",stResumeValue.u32DriCnt);
		JPEG_TRACE("===============================================================\n");
#endif
}
#endif /** END IF  CONFIG_JPEG_SUSPEND **/
