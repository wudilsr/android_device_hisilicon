/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_advca.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-09-16
Last Modified :
Description   :  
Function List :
History       :
******************************************************************************/
#include "ca_common.h"

HI_S32 HI_UNF_ADVCA_Init(HI_VOID);

HI_S32 HI_UNF_ADVCA_DeInit(HI_VOID);

HI_S32 HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

HI_S32 HI_UNF_ADVCA_SetRSAKey(HI_U8 *pkey);

HI_S32 HI_UNF_ADVCA_GetRSAKey(HI_U8 *pkey);

HI_S32 HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType);

HI_S32 HI_UNF_ADVCA_GetSecBootStat(HI_BOOL *pbEnable,HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType);

HI_S32 HI_UNF_ADVCA_SetOtpFuse(HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse, HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr);

HI_S32 HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse, HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr);

HI_S32 HI_UNF_ADVCA_CaVendorOperation(HI_UNF_ADVCA_VENDORID_E enCaVendor, HI_UNF_ADVCA_CA_VENDOR_OPT_S *pstCaVendorOpt);

/* The following interfaces are not standard UNF */
HI_S32 HI_UNF_ADVCA_GetVendorID(HI_U32 *pu32VendorID);

HI_S32 HI_UNF_ADVCA_GetChipId(HI_U32 *pu32ChipId);

HI_S32 HI_UNF_ADVCA_GetStbSn(HI_U8 au8StbSn[4]);






