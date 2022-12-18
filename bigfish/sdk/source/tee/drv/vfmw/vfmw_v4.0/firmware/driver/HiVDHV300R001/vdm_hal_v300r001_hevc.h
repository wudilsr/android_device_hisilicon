/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Hisilicon Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfvzHyMxSEsfcbL/G0fFswaAZ8tsS4we+PBWC6a/UNlzCWIaw+Ujkv9NAY+as0
fg7WZBW1+rJ9e1dpeF/osKiM5HH0uHCpB+CVvHcGDXNe/KQyGOBo1L3uPD4QKDVPyhbYzREy
wdTVwpwdAeJdqkgFpeqVt+xzghRJ2MewRhle+mqZuAbDkhR2FIGFOWxe8TgF2Q==*/
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

#ifndef __VDM_HAL_V300R001__HEVC_H__
#define __VDM_HAL_V300R001__HEVC_H__

#include "basedef.h"
#include "mem_manage.h"

#ifdef __cplusplus
extern "C" {
#endif

SINT32 HEVCHAL_V300R001_InitHal(SINT32 mn_phy_addr);
SINT32 HEVCHAL_V300R001_StartDec(HEVC_DEC_PIC_PARAM_S *pParam, SINT32 VdhId);

#ifdef __cplusplus
}
#endif


#endif //__VDM_HAL_HEVC_H__
