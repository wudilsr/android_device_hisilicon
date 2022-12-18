/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : optm_hal.h
Version             : Initial Draft
Author              : 
Created             : 2014/09/09
Description         : ALG��һ����������㷨�ṩ��
Function List       : 
History             :
Date                       Author                   Modification
2014/09/09                 y00181162                Created file        
******************************************************************************/

#ifndef __OPTM_HAL_H__
#define __OPTM_HAL_H__


/*********************************add include here******************************/
#ifndef HI_BUILD_IN_BOOT
#include <linux/kernel.h>
#endif


#include "optm_reg_define.h"
#include "optm_define.h"


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

HI_U32   OPTM_VDP_RegRead(HI_U32 a);
HI_VOID  OPTM_VDP_RegWrite(HI_U32 a, HI_U32 b);

HI_VOID  OPTM_VDP_DRIVER_Initial(HI_U32 virAddr);
#ifndef HI_BUILD_IN_BOOT
HI_VOID  OPTM_MDDRC_DRIVER_Initial(HI_U32 virAddr);
#endif
HI_VOID  OPTM_VDP_SetLayerConnect(HI_U32 u32Data);
HI_VOID  OPTM_VDP_OpenGFX3(HI_BOOL bOpen);


//-------------------------------------------------------------------
//VID_BEGIN
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//ZME_END
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//VID_END
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//GFX_BEGIN
//-------------------------------------------------------------------
#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetLayerAddr(HI_U32 u32Data, HI_U32 *pu32Addr);
HI_VOID OPTM_VDP_GFX_GetLayerEnable(HI_U32 u32Data, HI_U32 *pu32Enable );
HI_VOID OPTM_VDP_GP_GetRect      (HI_U32 u32Data, OPTM_VDP_DISP_RECT_S  *pstRect);
HI_VOID  OPTM_VDP_GFX_GetLayerInRect(HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *stInRect);
HI_VOID OPTM_VDP_GFX_GetLayerStride(HI_U32 u32Data, HI_U32 *pu32Stride);
HI_VOID OPTM_VDP_WBC_GetEnable(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 *pU32Enable);
HI_VOID OPTM_VDP_GFX_GetPalpha(HI_U32 u32Data, HI_U32 *pbAlphaEn,HI_U32 *pbArange,HI_U8 *pu8Alpha0,HI_U8 *pu8Alpha1);
HI_VOID OPTM_VDP_GFX_GetLayerGalpha(HI_U32 u32Data, HI_U8 *pu8Alpha0);
HI_VOID OPTM_VDP_GFX_GetKeyMask(HI_U32 u32Data, OPTM_VDP_GFX_MASK_S *pstMsk);
HI_VOID OPTM_VDP_GFX_GetColorKey(HI_U32 u32Data, HI_U32 *pbkeyEn,OPTM_VDP_GFX_CKEY_S *pstKey);
HI_VOID OPTM_VDP_GFX_GetPreMultEnable(HI_U32 u32Data, HI_U32 *pbEnable);
HI_VOID OPTM_VDP_GFX_GetInDataFmt(HI_U32 u32Data, OPTM_VDP_GFX_IFMT_E  *enDataFmt);

#endif


HI_VOID OPTM_VDP_CBM_GetMixerPrio(OPTM_VDP_CBM_MIX_E u32mixer_id, HI_U32 *pu32prio);
HI_VOID OPTM_VDP_SetMixgPrio(OPTM_VDP_CBM_MIX_E u32mixer_id,HI_U32 u32prio);

HI_VOID OPTM_VDP_GFX_SetLayerReso           (HI_U32 u32Data, OPTM_VDP_DISP_RECT_S stRect);
HI_VOID OPTM_VDP_GFX_SetVideoPos            (HI_U32 u32Data, OPTM_VDP_RECT_S  stRect);
HI_VOID OPTM_VDP_GFX_SetDispPos             (HI_U32 u32Data, OPTM_VDP_RECT_S  stRect);
HI_VOID OPTM_VDP_GFX_SetInReso              (HI_U32 u32Data, OPTM_VDP_RECT_S  stRect);
HI_VOID OPTM_VDP_GFX_SetLayerEnable         (HI_U32 u32Data, HI_U32 u32bEnable );
//HI_VOID OPTM_VDP_GFX_SetLayerAddr           (HI_U32 u32Data, HI_U32 u32LAddr, HI_U32 u32Stride);
HI_VOID OPTM_VDP_GFX_SetLayerAddrEX(HI_U32 u32Data, HI_U32 u32LAddr);
HI_VOID OPTM_VDP_GFX_SetLayerStride(HI_U32 u32Data, HI_U32 u32Stride);
HI_VOID OPTM_VDP_GFX_SetInDataFmt           (HI_U32 u32Data, OPTM_VDP_GFX_IFMT_E  enDataFmt);
HI_VOID OPTM_VDP_GFX_SetReadMode            (HI_U32 u32Data, HI_U32 u32Mode);
HI_VOID OPTM_VDP_GFX_SetBitExtend           (HI_U32 u32Data, OPTM_VDP_GFX_BITEXTEND_E u32mode);
HI_VOID OPTM_VDP_GFX_SetColorKey            (HI_U32 u32Data, HI_U32  bkeyEn,OPTM_VDP_GFX_CKEY_S stKey );
HI_VOID OPTM_VDP_GFX_SetKeyMask             (HI_U32 u32Data, OPTM_VDP_GFX_MASK_S stMsk);
//lut read update
HI_VOID  OPTM_VDP_GFX_SetParaUpd            (HI_U32 u32Data, OPTM_VDP_DISP_COEFMODE_E enMode );
HI_VOID OPTM_VDP_GFX_SetLutAddr             (HI_U32 u32Data, HI_U32 u32LutAddr);

HI_VOID  OPTM_VDP_GFX_SetNoSecFlag    (HI_U32 u32Data, HI_U32 u32Enable );
HI_VOID  OPTM_VDP_GFX_SetDcmpEnable(HI_U32 u32Data, HI_U32 u32bEnable);
//HI_VOID OPTM_VDP_GFX_SetDcmpAddr(HI_U32 u32Data, HI_U32 u32LAddr);
//HI_VOID OPTM_VDP_GFX_SetDcmpNAddr(HI_U32 u32Data, HI_U32 u32NAddr);
HI_VOID OPTM_VDP_GFX_SetDcmpOffset(HI_U32 u32Data, HI_U32 u32Offset);




//3D
#ifndef HI_BUILD_IN_BOOT
HI_VOID  OPTM_VDP_GFX_SetThreeDimDofEnable    (HI_U32 u32Data, HI_U32 bEnable);
HI_VOID  OPTM_VDP_GFX_SetThreeDimDofStep(HI_U32 u32Data, HI_S32 s32LStep, HI_S32 s32RStep);
HI_VOID OPTM_VDP_GFX_SetThreeDimEnable      (HI_U32 u32Data, HI_U32 bTrue);
HI_VOID VDP_GFX_SetSrcMode             (HI_U32 u32Data, HI_U32 u32SrcMode);

HI_VOID OPTM_VDP_GFX_SetDofEnable           (HI_U32 u32Data, HI_U32 bTrue);
HI_VOID OPTM_VDP_GFX_SetDofFmt              (HI_U32 u32Data, HI_U32 u32DataFmt);
HI_VOID OPTM_VDP_GFX_SetDofStep             (HI_U32 u32Data, HI_U32 u32eye_sel,HI_U32 u32step);
//HI_VOID OPTM_VDP_GFX_SetDispMode            (HI_U32 u32Data, OPTM_VDP_DISP_MODE_E enDispMode);

//HI_VOID OPTM_VDP_GFX_SetGammaEnable          (HI_U32 u32Data, HI_U32 u32GmmEn);
#endif

//HI_VOID  OPTM_VDP_GFX_SetFlipEnable         (HI_U32 u32Data, HI_U32 bEnable);
HI_VOID  OPTM_VDP_GFX_SetPreMultEnable      (HI_U32 u32Data, HI_U32 bEnable);

HI_VOID  OPTM_VDP_GFX_SetLayerBkg           (HI_U32 u32Data, OPTM_VDP_BKG_S stBkg);
HI_VOID  OPTM_VDP_GFX_SetLayerGalpha        (HI_U32 u32Data, HI_U32 u32Alpha0);
HI_VOID  OPTM_VDP_GFX_SetPalpha             (HI_U32 u32Data, HI_U32 bAlphaEn,HI_U32 bArange,HI_U32 u32Alpha0,HI_U32 u32Alpha1);

//HI_VOID  VDP_GFX_SetCmpAddr            (HI_U32 u32Data, HI_U32 u32CmpAddr);
#ifndef HI_BUILD_IN_BOOT
HI_VOID  OPTM_VDP_GFX_SetLayerNAddr         (HI_U32 u32Data, HI_U32 u32NAddr);
#endif
//HI_VOID  OPTM_VDP_GFX_SetMuteEnable         (HI_U32 u32Data, HI_U32 bEnable);
HI_VOID  OPTM_VDP_GFX_SetUpdMode            (HI_U32 u32Data, HI_U32 u32Mode);
HI_VOID  OPTM_VDP_GFX_SetDeCmpEnable        (HI_U32 u32Data, HI_U32 bEnable);

HI_VOID  OPTM_VDP_GFX_SetRegUp              (HI_U32 u32Data);


////Zme
//HI_VOID  VDP_GFX_SetZmeEnable          (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_U32 bEnable);
//HI_VOID  VDP_GFX_SetZmeFirEnable       (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_U32 bEnable);
//HI_VOID  VDP_GFX_SetZmeMidEnable       (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_U32 bEnable);
//HI_VOID  VDP_GFX_SetZmeHfirOrder       (HI_U32 u32Data, HI_U32 uHfirOrder);
//HI_VOID  VDP_GFX_SetZmeVerTap          (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_U32 u32VerTap);
//HI_VOID  VDP_GFX_SetZmePhase           (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_S32 s32Phase);


//-------------------------------------------------------------------
//GFX_END
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//GP_BEGIN
//-------------------------------------------------------------------
HI_VOID OPTM_VDP_GP_SetLayerReso            (HI_U32 u32Data, OPTM_VDP_DISP_RECT_S  stRect);
//HI_VOID OPTM_VDP_GP_SetVideoPos             (HI_U32 u32Data, OPTM_VDP_RECT_S  stRect);
//HI_VOID OPTM_VDP_GP_SetDispPos              (HI_U32 u32Data, OPTM_VDP_RECT_S  stRect);
//HI_VOID OPTM_VDP_GP_SetInReso               (HI_U32 u32Data, OPTM_VDP_RECT_S  stRect);
//HI_VOID OPTM_VDP_GP_SetOutReso              (HI_U32 u32Data, OPTM_VDP_RECT_S  stRect);
HI_VOID OPTM_VDP_GP_SetIpOrder              (HI_U32 u32Data, HI_U32 u32Chn, OPTM_VDP_GP_ORDER_E enIpOrder);
HI_VOID OPTM_VDP_GP_SetReadMode             (HI_U32 u32Data, HI_U32 u32Mode);
HI_VOID OPTM_VDP_GP_SetParaUpd              (HI_U32 u32Data, OPTM_VDP_GP_PARA_E enMode);
//HI_VOID OPTM_VDP_GP_SetRect                 (HI_U32 u32Data, OPTM_VDP_DISP_RECT_S  stRect);
HI_VOID OPTM_VDP_GP_SetRegUp                (HI_U32 u32Data);
HI_VOID OPTM_VDP_GP_SetLayerGalpha          (HI_U32 u32Data, HI_U32 u32Alpha);
//HI_VOID OPTM_VDP_GP_SetLayerBkg             (HI_U32 u32Data, OPTM_VDP_BKG_S stBkg);

//GP_CSC_BEGIN
HI_VOID OPTM_VDP_GP_SetCscDcCoef            (HI_U32 u32Data, OPTM_VDP_CSC_DC_COEF_S pstCscCoef);
HI_VOID OPTM_VDP_GP_SetCscCoef              (HI_U32 u32Data, OPTM_VDP_CSC_COEF_S stCscCoef);
HI_VOID OPTM_VDP_GP_SetCscEnable            (HI_U32 u32Data, HI_U32 u32bCscEn);
//HI_VOID OPTM_VDP_GP_SetCscMode              (HI_U32 u32Data, OPTM_VDP_CSC_MODE_E enCscMode);
//HI_VOID OPTM_VDP_GP_SetDispMode             (HI_U32 u32Data, OPTM_VDP_DISP_MODE_E enDispMode);



HI_VOID OPTM_VDP_GP_SetZmeEnable           (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID OPTM_VDP_GP_SetZmePhase            (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_S32 s32Phase);
HI_VOID OPTM_VDP_GP_SetZmeFirEnable        (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID OPTM_VDP_GP_SetZmeMidEnable        (HI_U32 u32Data, OPTM_VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID OPTM_VDP_GP_SetZmeHorRatio         (HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID OPTM_VDP_GP_SetZmeVerRatio         (HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID OPTM_VDP_GP_SetZmeHfirOrder        (HI_U32 u32Data, HI_U32 u32HfirOrder);
HI_VOID OPTM_VDP_GP_SetZmeCoefAddr         (HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32Addr);
//HI_VOID OPTM_VDP_GP_SetParaRd              (HI_U32 u32Data, OPTM_VDP_GP_PARA_E enMode);

//GTI
HI_VOID  OPTM_VDP_GP_SetTiEnable           (HI_U32 u32Data, HI_U32 u32Md,HI_U32 u32Data1);
HI_VOID  OPTM_VDP_GP_SetTiGainRatio        (HI_U32 u32Data, HI_U32 u32Md, HI_S32 s32Data);
HI_VOID  OPTM_VDP_GP_SetTiMixRatio         (HI_U32 u32Data, HI_U32 u32Md, HI_U32 u32mixing_ratio);
HI_VOID  OPTM_VDP_GP_SetTiHfThd            (HI_U32 u32Data, HI_U32 u32Md, HI_U32 * u32TiHfThd);
HI_VOID  OPTM_VDP_GP_SetTiHpCoef           (HI_U32 u32Data, HI_U32 u32Md, HI_S32 * s32Data);
HI_VOID  OPTM_VDP_GP_SetTiCoringThd        (HI_U32 u32Data, HI_U32 u32Md, HI_U32 u32thd);
HI_VOID  OPTM_VDP_GP_SetTiSwingThd         (HI_U32 u32Data, HI_U32 u32Md, HI_U32 u32thd, HI_U32 u32thd1);
HI_VOID  OPTM_VDP_GP_SetTiGainCoef         (HI_U32 u32Data, HI_U32 u32Md, HI_U32 * u32coef);
//HI_VOID  OPTM_VDP_GP_SetTiDefThd           (HI_U32 u32Data, HI_U32 u32Md);

//-------------------------------------------------------------------
//GPX_END
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//Bus Function BEGIN

//Bus Function END
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//DISP_BEGIN
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//DISP_END
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//MIXER_BEGIN
//-------------------------------------------------------------------
HI_VOID OPTM_VDP_CBM_SetMixerBkg              (OPTM_VDP_CBM_MIX_E u32mixer_id, OPTM_VDP_BKG_S stBkg);
HI_VOID OPTM_VDP_CBM_SetMixerPrio             (OPTM_VDP_CBM_MIX_E u32mixer_id, HI_U32 u32layer_id,HI_U32 u32prio);
//HI_VOID OPTM_VDP_CBM_ResetMixerPrio           (OPTM_VDP_CBM_MIX_E u32mixer_id);

//-------------------------------------------------------------------
//MIXER_END
//-------------------------------------------------------------------
////-------------------------------------------------------------------
//CBAR_BEGIN
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//CBAR_END
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//IPU_BEGIN
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//IPU_END
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//WBC_DHD0_BEGIN
//-------------------------------------------------------------------
HI_VOID OPTM_VDP_WBC_SetEnable              (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bEnable);
HI_VOID OPTM_VDP_WBC_SetOutIntf             (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DATA_RMODE_E u32RdMode);
HI_VOID OPTM_VDP_WBC_SetOutFmt              (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_WBC_OFMT_E stIntfFmt);
//HI_VOID OPTM_VDP_WBC_SetSpd                 (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32ReqSpd);
HI_VOID OPTM_VDP_WBC_SetLayerAddr           (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32LAddr,HI_U32 u32CAddr,HI_U32 u32LStr, HI_U32 u32CStr);
HI_VOID OPTM_VDP_WBC_SetLayerReso           (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DISP_RECT_S  stRect);
HI_VOID OPTM_VDP_WBC_SetDitherMode          (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DITHER_E enDitherMode);
//HI_VOID OPTM_VDP_WBC_SetDitherCoef          (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DITHER_COEF_S dither_coef);
HI_VOID OPTM_VDP_WBC_SetCropReso            (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DISP_RECT_S stRect);
HI_VOID OPTM_VDP_WBC_SetRegUp               (OPTM_VDP_LAYER_WBC_E enLayer);

//HI_VOID OPTM_VDP_WBC_SetZmeCoefAddr         (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_WBC_PARA_E u32Mode, HI_U32 u32Addr);
//HI_VOID OPTM_VDP_WBC_SetParaUpd             (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_WBC_PARA_E enMode);
//HI_VOID OPTM_VDP_WBC_SetSfifo               (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32Data );
//HI_VOID OPTM_VDP_WBC_SetZmeEnable           (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
//HI_VOID OPTM_VDP_WBC_SetMidEnable           (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_ZME_MODE_E enMode, HI_U32 bEnable);
//HI_VOID OPTM_VDP_WBC_SetFirEnable           (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_ZME_MODE_E enMode, HI_U32 bEnable);
//HI_VOID OPTM_VDP_WBC_SetZmeVerTap           (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_ZME_MODE_E enMode, HI_U32 u32VerTap);
//HI_VOID OPTM_VDP_WBC_SetZmeHfirOrder        (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32HfirOrder);
//HI_VOID OPTM_VDP_WBC_SetZmeHorRatio         (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio);
//HI_VOID OPTM_VDP_WBC_SetZmeInFmt            (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_PROC_FMT_E u32Fmt);
//HI_VOID OPTM_VDP_WBC_SetZmeOutFmt           (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_PROC_FMT_E u32Fmt);
//HI_VOID OPTM_VDP_WBC_SetZmeVerRatio         (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio);
//HI_VOID OPTM_VDP_WBC_SetZmePhase            (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_ZME_MODE_E enMode,HI_S32 s32Phase);
//HI_VOID OPTM_VDP_WBC_SetCscEnable           (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 enCSC);
//HI_VOID OPTM_VDP_WBC_SetCscDcCoef           (OPTM_VDP_LAYER_WBC_E enLayer,OPTM_VDP_CSC_DC_COEF_S stCscCoef);
//HI_VOID OPTM_VDP_WBC_SetCscCoef             (OPTM_VDP_LAYER_WBC_E enLayer,OPTM_VDP_CSC_COEF_S stCscCoef);
//HI_VOID OPTM_VDP_WBC_SetCscMode             (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_CSC_MODE_E enCscMode);
HI_VOID OPTM_VDP_WBC_SetAutoSt(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bEnable);
HI_VOID OPTM_VDP_WBC_SetThreeMd(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bMode);



HI_VOID OPTM_VDP_WBC_SetCmpEnable( OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bEnable);
HI_VOID OPTM_VDP_WBC_SetCmpDrr( OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32CmpDrr);
HI_VOID OPTM_VDP_WBC_SetLossy( OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bEnable);
HI_VOID OPTM_VDP_WBC_SetOffSet(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32Offset);

HI_U32 OPTM_VDP_DISP_GetIntSignal(HI_U32 u32intmask);
HI_VOID OPTM_ClearIntSignal(HI_U32 u32intmask);
HI_VOID  OPTM_VDP_SetCMPAddr   (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32ARddr,HI_U32 u32GBddr);
HI_VOID  OPTM_VDP_SetDCMPAddr (HI_U32 u32Data, HI_U32 u32ARddr,HI_U32 u32GBddr);
HI_VOID  OPTM_VDP_SetCMPStride  (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32Stride);
HI_VOID  OPTM_VDP_SetDCMPStride(HI_U32 u32Data, HI_U32 u32Stride);
HI_VOID  OPTM_VDP_SetCMPInRect (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_RECT_S *pstRect);
HI_VOID  OPTM_VDP_WBC_SetCMPOutSize(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32Width, HI_U32 u32Height);
HI_VOID  OPTM_MDDRC_SetZoneAddr(HI_U32 u32Section, HI_U32 u32StartAddr, HI_U32 u32EndAddr);
HI_VOID  OPTM_MDDRC_GetStatus(HI_U32 *u32Status);
OPTM_VDP_DISP_MODE_E OPTM_DISP_GetDispMode  (HI_U32 u32Data);



#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __OPTM_HAL_H__ */
