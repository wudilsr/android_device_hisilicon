/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Hisilicon Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfvzHyMxSEsfcbL/G0fFswaAZ8tsS4we+PBWC6a/UNlzCWIaw+Ujkv9NAY+as0
fg7WZCM52l645cSV2LGOXS6KLc9drc3189LAsyHQ7oh7h2mp9Dmv432sPkr5Kn73fNaNZa9+
hg9FcsQDoJTb12z5OKtJ1ZiKTC3oBWTQhlrmOmRqb/cTQdxRTar5SMB3bkTzhg==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************

  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
    �� �� ��   : vdmv300plus_hal.h
    �� �� ��   : ����
    ��    ��   : 
    ��������   : 
    ����޸�   :
    ��������   : VDMV300plusӲ������
         

  �޸���ʷ   :
    1.��    �� : 2009-03-04
    ��    ��   : 
    �޸�����   : 

******************************************************************************/

#ifndef __VDM_HAL_V300R001_H264_H__
#define __VDM_HAL_V300R001_H264_H__

#include "basedef.h"
#include "mem_manage.h"

#ifdef __cplusplus
extern "C" {
#endif

SINT32 H264HAL_V300R001_InitHal(SINT32 H264MnAddr);
SINT32 H264HAL_V300R001_StartDec(H264_DEC_PIC_PARAM_S *pParam, SINT32 VdhId);

#ifdef __cplusplus
}
#endif


#endif //__VDM_HAL_H264_H__
