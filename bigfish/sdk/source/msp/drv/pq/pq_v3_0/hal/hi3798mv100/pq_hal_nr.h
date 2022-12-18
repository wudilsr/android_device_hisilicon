/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_csc.h
  Version       : Initial Draft
  Author        : Hisilicon PQ software group
  Created       : 2013/11/13
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_NR_H__
#define __PQ_HAL_NR_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/*nr config parameter*/
typedef struct hiTNR_PARAMETER_S
{
	HI_S32 TNREn;
	HI_S32 YNr1dEn;
	HI_S32 CNr1dEn;
	HI_S32 YByPass;
	HI_S32 CByPass;
	
	HI_S32 TMotionYMTMeanMode;
	HI_S32 TMotionCMTMode;
	HI_S32 TMotionYMTMode;
	HI_S32 TMotionCMTMeanMode;
	
	HI_S32 TEdgeYLPFMode;
	HI_S32 TEdgeCLPFMode;
	HI_S32 TMotionLPFMode;
	HI_S32 MarketModeEn;
	HI_S32 MarketModeLR;
	
	HI_S32 TMotionYMTMeanRatioEn;
	HI_S32 TMotionYMTMappingMax;
	HI_S32 TMotionYMTMappingMin;
	HI_S32 TMotionYMTMappingR0;
	HI_S32 TMotionYMTMappingR1;
	HI_S32 TMotionYMTMappingR2;
	HI_S32 TMotionYMTMappingR3;
	HI_S32 TMotionYMTMappingR4;
	HI_S32 TMotionYMTMappingT1;
	HI_S32 TMotionYMTMappingT2;
	HI_S32 TMotionYMTMappingT3;
	HI_S32 TMotionYMTMappingT4;
	HI_S32 TMotionYMTMappingT5;
	HI_S32 TMotionYMTMappingT6;
	HI_S32 TMotionYMTMappingK1;
	HI_S32 TMotionYMTMappingK2;
	HI_S32 TMotionYMTMappingK3;
	HI_S32 TMotionYMTMappingK4;

	HI_S32 TMotionCMTMeanRatioEn;
	HI_S32 TMotionCMTMappingMax;
	HI_S32 TMotionCMTMappingMin;
	HI_S32 TMotionCMTMappingR0;
	HI_S32 TMotionCMTMappingR1;
	HI_S32 TMotionCMTMappingR2;
	HI_S32 TMotionCMTMappingR3;
	HI_S32 TMotionCMTMappingR4;
	HI_S32 TMotionCMTMappingT1;
	HI_S32 TMotionCMTMappingT2;
	HI_S32 TMotionCMTMappingT3;
	HI_S32 TMotionCMTMappingT4;
	HI_S32 TMotionCMTMappingT5;
	HI_S32 TMotionCMTMappingT6;
	HI_S32 TMotionCMTMappingK1;
	HI_S32 TMotionCMTMappingK2;
	HI_S32 TMotionCMTMappingK3;
	HI_S32 TMotionCMTMappingK4;

	//Y PixMean to ratio
	HI_S32 TMotionYMTMeanRatioMax;
	HI_S32 TMotionYMTMeanRatioMin;
	HI_S32 TMotionYMTMeanRatioR0;
	HI_S32 TMotionYMTMeanRatioR1;
	HI_S32 TMotionYMTMeanRatioR2;
	HI_S32 TMotionYMTMeanRatioR3;
	HI_S32 TMotionYMTMeanRatioR4;
	HI_S32 TMotionYMTMeanRatioT1;
	HI_S32 TMotionYMTMeanRatioT2;
	HI_S32 TMotionYMTMeanRatioT3;
	HI_S32 TMotionYMTMeanRatioT4;
	HI_S32 TMotionYMTMeanRatioT5;
	HI_S32 TMotionYMTMeanRatioT6;
	HI_S32 TMotionYMTMeanRatioK1;
	HI_S32 TMotionYMTMeanRatioK2;
	HI_S32 TMotionYMTMeanRatioK3;
	HI_S32 TMotionYMTMeanRatioK4;

	//C PixMean to ratio
	HI_S32 TMotionCMTMeanRatioMax;
	HI_S32 TMotionCMTMeanRatioMin;
	HI_S32 TMotionCMTMeanRatioR0;
	HI_S32 TMotionCMTMeanRatioR1;
	HI_S32 TMotionCMTMeanRatioR2;
	HI_S32 TMotionCMTMeanRatioR3;
	HI_S32 TMotionCMTMeanRatioR4;
	HI_S32 TMotionCMTMeanRatioT1;
	HI_S32 TMotionCMTMeanRatioT2;
	HI_S32 TMotionCMTMeanRatioT3;
	HI_S32 TMotionCMTMeanRatioT4;
	HI_S32 TMotionCMTMeanRatioT5;
	HI_S32 TMotionCMTMeanRatioT6;
	HI_S32 TMotionCMTMeanRatioK1;
	HI_S32 TMotionCMTMeanRatioK2;
	HI_S32 TMotionCMTMeanRatioK3;
	HI_S32 TMotionCMTMeanRatioK4;

	//Sum of Coe must be 32
	HI_S32 TMotionYCMTCoe0;
	HI_S32 TMotionYCMTCoe1;
	HI_S32 TMotionYCMTCoe2;
	HI_S32 TMotionYCMTCoe3;
	HI_S32 TMotionYCMTCoe4;

	//Sum of Coe must be 32
	HI_S32 TMotionLPFCoe0;
	HI_S32 TMotionLPFCoe1;
	HI_S32 TMotionLPFCoe2;
	HI_S32 TMotionLPFCoe3;
	HI_S32 TMotionLPFCoe4;
	
	HI_S32 TMotionYMTCore;
	HI_S32 TMotionYMTK;
	HI_S32 TMotionYMTMeanCore;
	HI_S32 TMotionYMTMeanK;

	HI_S32 TMotionCMTCore;
	HI_S32 TMotionCMTK;
	HI_S32 TMotionCMTMeanCore;
	HI_S32 TMotionCMTMeanK;
	
	HI_S32 TEdgeYEGMeanMode;
	HI_S32 TEdgeCEGMeanMode;
	HI_S32 TEdgeYHPF1Coef0;
	HI_S32 TEdgeYHPF1Coef1;
	HI_S32 TEdgeYHPF1Coef2;
	HI_S32 TEdgeYHPF1Coef3;
	HI_S32 TEdgeYHPF1Coef4;
	HI_S32 TEdgeYHPF1Coef5;
	HI_S32 TEdgeYHPF1Coef6;
	HI_S32 TEdgeYHPF1Coef7;
	HI_S32 TEdgeYHPF1Coef8;
	HI_S32 TEdgeYHPF1LShift;
	HI_S32 TEdgeYHPF2Coef0;
	HI_S32 TEdgeYHPF2Coef1;
	HI_S32 TEdgeYHPF2Coef2;
	HI_S32 TEdgeYHPF2Coef3;
	HI_S32 TEdgeYHPF2Coef4;
	HI_S32 TEdgeYHPF2Coef5;
	HI_S32 TEdgeYHPF2Coef6;
	HI_S32 TEdgeYHPF2Coef7;
	HI_S32 TEdgeYHPF2Coef8;
	HI_S32 TEdgeYHPF2LShift;
	HI_S32 TEdgeYHPF3Coef0;
	HI_S32 TEdgeYHPF3Coef1;
	HI_S32 TEdgeYHPF3Coef2;
	HI_S32 TEdgeYHPF3Coef3;
	HI_S32 TEdgeYHPF3Coef4;
	HI_S32 TEdgeYHPF3Coef5;
	HI_S32 TEdgeYHPF3Coef6;
	HI_S32 TEdgeYHPF3Coef7;
	HI_S32 TEdgeYHPF3Coef8;
	HI_S32 TEdgeYHPF3LShift;
	HI_S32 TEdgeYHPF4Coef0;
	HI_S32 TEdgeYHPF4Coef1;
	HI_S32 TEdgeYHPF4Coef2;
	HI_S32 TEdgeYHPF4Coef3;
	HI_S32 TEdgeYHPF4Coef4;
	HI_S32 TEdgeYHPF4Coef5;
	HI_S32 TEdgeYHPF4Coef6;
	HI_S32 TEdgeYHPF4Coef7;
	HI_S32 TEdgeYHPF4Coef8;
	HI_S32 TEdgeYHPF4LShift;

	HI_S32 TEdgeYMTMeanLPFCoef0;
	HI_S32 TEdgeYMTMeanLPFCoef1;
	HI_S32 TEdgeYMTMeanLPFCoef2;
	HI_S32 TEdgeYMTMeanLPFCoef3;
	HI_S32 TEdgeYMTMeanLPFCoef4;
	HI_S32 TEdgeYMTMeanLPFCoef5;
	HI_S32 TEdgeYMTMeanLPFCoef6;
	HI_S32 TEdgeYMTMeanLPFCoef7;
	HI_S32 TEdgeYMTMeanLPFCoef8;

	HI_S32 TEdgeYCEGMeanRatioEn;
	HI_S32 TEdgeYCEGMeanRatioMax;
	HI_S32 TEdgeYCEGMeanRatioMin;
	HI_S32 TEdgeYCEGMeanRatioR0;
	HI_S32 TEdgeYCEGMeanRatioR1;
	HI_S32 TEdgeYCEGMeanRatioR2;
	HI_S32 TEdgeYCEGMeanRatioR3;
	HI_S32 TEdgeYCEGMeanRatioR4;
	HI_S32 TEdgeYCEGMeanRatioT1;
	HI_S32 TEdgeYCEGMeanRatioT2;
	HI_S32 TEdgeYCEGMeanRatioT3;
	HI_S32 TEdgeYCEGMeanRatioT4;
	HI_S32 TEdgeYCEGMeanRatioT5;
	HI_S32 TEdgeYCEGMeanRatioT6;
	HI_S32 TEdgeYCEGMeanRatioK1;
	HI_S32 TEdgeYCEGMeanRatioK2;
	HI_S32 TEdgeYCEGMeanRatioK3;
	HI_S32 TEdgeYCEGMeanRatioK4;

	HI_S32 TEdgeYCMTMeanRatioEn;
	HI_S32 TEdgeYCMTMeanRatioMax;
	HI_S32 TEdgeYCMTMeanRatioMin;
	HI_S32 TEdgeYCMTMeanRatioR0;
	HI_S32 TEdgeYCMTMeanRatioR1;
	HI_S32 TEdgeYCMTMeanRatioR2;
	HI_S32 TEdgeYCMTMeanRatioR3;
	HI_S32 TEdgeYCMTMeanRatioR4;
	HI_S32 TEdgeYCMTMeanRatioT1;
	HI_S32 TEdgeYCMTMeanRatioT2;
	HI_S32 TEdgeYCMTMeanRatioT3;
	HI_S32 TEdgeYCMTMeanRatioT4;
	HI_S32 TEdgeYCMTMeanRatioT5;
	HI_S32 TEdgeYCMTMeanRatioT6;
	HI_S32 TEdgeYCMTMeanRatioK1;
	HI_S32 TEdgeYCMTMeanRatioK2;
	HI_S32 TEdgeYCMTMeanRatioK3;
	HI_S32 TEdgeYCMTMeanRatioK4;

	HI_S32 TEdgeYCMTMappingMax;
	HI_S32 TEdgeYCMTMappingMin;
	HI_S32 TEdgeYCMTMappingR0;
	HI_S32 TEdgeYCMTMappingR1;
	HI_S32 TEdgeYCMTMappingR2;
	HI_S32 TEdgeYCMTMappingR3;
	HI_S32 TEdgeYCMTMappingR4;
	HI_S32 TEdgeYCMTMappingT1;
	HI_S32 TEdgeYCMTMappingT2;
	HI_S32 TEdgeYCMTMappingT3;
	HI_S32 TEdgeYCMTMappingT4;
	HI_S32 TEdgeYCMTMappingT5;
	HI_S32 TEdgeYCMTMappingT6;
	HI_S32 TEdgeYCMTMappingK1;
	HI_S32 TEdgeYCMTMappingK2;
	HI_S32 TEdgeYCMTMappingK3;
	HI_S32 TEdgeYCMTMappingK4;

	HI_S32 TEdgeYCEGMappingMax;
	HI_S32 TEdgeYCEGMappingMin;
	HI_S32 TEdgeYCEGMappingR0;
	HI_S32 TEdgeYCEGMappingR1;
	HI_S32 TEdgeYCEGMappingR2;
	HI_S32 TEdgeYCEGMappingR3;
	HI_S32 TEdgeYCEGMappingR4;
	HI_S32 TEdgeYCEGMappingT1;
	HI_S32 TEdgeYCEGMappingT2;
	HI_S32 TEdgeYCEGMappingT3;
	HI_S32 TEdgeYCEGMappingT4;
	HI_S32 TEdgeYCEGMappingT5;
	HI_S32 TEdgeYCEGMappingT6;
	HI_S32 TEdgeYCEGMappingK1;
	HI_S32 TEdgeYCEGMappingK2;
	HI_S32 TEdgeYCEGMappingK3;
	HI_S32 TEdgeYCEGMappingK4;
	
	HI_S32 TEdgeYCEGMode;
	HI_S32 TEdgeYEGCore1;
	HI_S32 TEdgeYEGK1;
	HI_S32 TEdgeYMTCore1;
	HI_S32 TEdgeYMTK1;
	HI_S32 TEdgeYMTCore2;
	HI_S32 TEdgeYMTK2;

	HI_S32 TEdgeYMTCore;
	HI_S32 TEdgeYMTK;
	HI_S32 TEdgeYEGCore;
	HI_S32 TEdgeYEGK;
	HI_S32 TEdgeYRShift;
	
	HI_S32 TEdgeYEGWeight1;
	HI_S32 TEdgeYEGWeight2;
	HI_S32 TEdgeYEGWeight3;
	HI_S32 TEdgeYEGWeight4;

	HI_S32 TEdgeCEGWeight1;
	HI_S32 TEdgeCEGWeight2;
	HI_S32 TEdgeCEGWeight3;
	HI_S32 TEdgeCEGWeight4;

	HI_S32 TEdgeYMovingCore;
	HI_S32 TEdgeYMovingK;

	HI_S32 TEdgeCHPF4Coef0;
	HI_S32 TEdgeCHPF4Coef1;
	HI_S32 TEdgeCHPF4Coef2;
	HI_S32 TEdgeCHPF4Coef3;
	HI_S32 TEdgeCHPF4Coef4;
	HI_S32 TEdgeCHPF4Coef5;
	HI_S32 TEdgeCHPF4Coef6;
	HI_S32 TEdgeCHPF4Coef7;
	HI_S32 TEdgeCHPF4Coef8;
	HI_S32 TEdgeCHPF4LShift;
	HI_S32 TEdgeCMeanLPFCoef0;
	HI_S32 TEdgeCMeanLPFCoef1;
	HI_S32 TEdgeCMeanLPFCoef2;
	HI_S32 TEdgeCMeanLPFCoef3;
	HI_S32 TEdgeCMeanLPFCoef4;
	HI_S32 TEdgeCMeanLPFCoef5;
	HI_S32 TEdgeCMeanLPFCoef6;
	HI_S32 TEdgeCMeanLPFCoef7;
	HI_S32 TEdgeCMeanLPFCoef8;
	
	HI_S32 TEdgeCEGCore2;
	HI_S32 TEdgeCEGK2;
	HI_S32 TEdgeCMTCore2;
	HI_S32 TEdgeCMTK2;
	HI_S32 TEdgeCMTCore3;
	HI_S32 TEdgeCMTK3;
	HI_S32 TEdgeCMTCore1;
	HI_S32 TEdgeCMTK1;
	HI_S32 TEdgeCEGCore;
	HI_S32 TEdgeCEGK;
	HI_S32 TEdgeCRShift;
	
	HI_S32 TMTYMotionCore;
	HI_S32 TMTYMotionK;
	HI_S32 TMTYEdgeCore;
	HI_S32 TMTYEdgeK;
	HI_S32 TMTCMotionCore;
	HI_S32 TMTCMotionK;
	HI_S32 TMTCEdgeCore;
	HI_S32 TMTCEdgeK;
	
	HI_S32 TMT2DUpdate;
	HI_S32 TMTCbCrUpdate;

	HI_S32 TFnlMotionYMappingMax;
	HI_S32 TFnlMotionYMappingMin;
	HI_S32 TFnlMotionYMappingR0;
	HI_S32 TFnlMotionYMappingR1;
	HI_S32 TFnlMotionYMappingR2;
	HI_S32 TFnlMotionYMappingR3;
	HI_S32 TFnlMotionYMappingR4;
	HI_S32 TFnlMotionYMappingT1;
	HI_S32 TFnlMotionYMappingT2;
	HI_S32 TFnlMotionYMappingT3;
	HI_S32 TFnlMotionYMappingT4;
	HI_S32 TFnlMotionYMappingT5;
	HI_S32 TFnlMotionYMappingT6;
	HI_S32 TFnlMotionYMappingK1;
	HI_S32 TFnlMotionYMappingK2;
	HI_S32 TFnlMotionYMappingK3;
	HI_S32 TFnlMotionYMappingK4;

	HI_S32 TFnlMotionCMappingMax;
	HI_S32 TFnlMotionCMappingMin;
	HI_S32 TFnlMotionCMappingR0;
	HI_S32 TFnlMotionCMappingR1;
	HI_S32 TFnlMotionCMappingR2;
	HI_S32 TFnlMotionCMappingR3;
	HI_S32 TFnlMotionCMappingR4;
	HI_S32 TFnlMotionCMappingT1;
	HI_S32 TFnlMotionCMappingT2;
	HI_S32 TFnlMotionCMappingT3;
	HI_S32 TFnlMotionCMappingT4;
	HI_S32 TFnlMotionCMappingT5;
	HI_S32 TFnlMotionCMappingT6;
	HI_S32 TFnlMotionCMappingK1;
	HI_S32 TFnlMotionCMappingK2;
	HI_S32 TFnlMotionCMappingK3;
	HI_S32 TFnlMotionCMappingK4;
	
	HI_S32 TMotionHisTerm1;
	HI_S32 TMotionHisTerm2;
	HI_S32 TMotionHisAlpha1;
	HI_S32 TMotionHisAlpha2;
	
	HI_S32 T2DMMEn;
	HI_S32 T2DMedEn;
	HI_S32 T2dMeanEn;
	HI_S32 T2DEdgeMode;
	HI_S32 T2DEdgeK;
	HI_S32 T2DEdgeCore;
	HI_S32 T2DNoiseK;
	HI_S32 T2DNoiseCore;
	HI_S32 TMotionFinalFilterMode;
	HI_S32 TMotionFinalFilterEn;
	HI_S32 TMotionCalcMode;
	
	HI_S32 TSceneChangeEn;
	HI_S32 TSceneChangeforMotionEn;
	HI_S32 TSceneChangeforMotionCore;
	HI_S32 TSceneChangeforMotionK;

	HI_S32 TGlobalMotionEn;
	HI_S32 TGlobalMotionCore;
	HI_S32 TGlobalMotionK;

	HI_S32 TEdgeCMovingCore;
	HI_S32 TEdgeCMovingK;

	HI_S32 TEdgeCMovingLPFMode;
	HI_S32 TEdgeYMovingLPFMode;
	HI_S32 TMTCbCrUpdateMode;
	HI_S32 TMotionFinalLPFMode1DMode;
	HI_S32 YMotionMode;
	HI_S32 CMotionMode;

	HI_S32 TYMYCore;
	HI_S32 TYMYK;
	HI_S32 TYMEYCore;
	HI_S32 TYMEYK;

	HI_S32 TCMYCore;
	HI_S32 TCMYK;
	HI_S32 TCMEYCore;
	HI_S32 TCMEYK;

	HI_S32 TYRandNoiseEn;
	HI_S32 TYRandNoiseBits;
	HI_S32 TCRandNoiseEn;
	HI_S32 TCRandNoiseBits;
	HI_S32 THisMotionEn;

	HI_U16 TLUT_Motion_Noise[128];
	HI_U16 TLUT_Motion_Edge[128];
	HI_U16 TLUT_CbCr[16][32];
	HI_U16 TLUT_MotionEdge_Ratio[8][8];
	HI_S32 TGMGetMode;
	HI_S32 TSmallMotionThdPglb;
	HI_S32 TLargeMotionThdPglb;
	HI_S32 TMotionLfshiftPglb;
	
	HI_S32 TGMBitDepth;
	HI_U16 Reserved_373;
	HI_U16 Reserved_380;
	HI_U32 u32TnrGlbMtnEnable;
}TNR_PARAMETER_S;



typedef struct  hiSNR_PARAMETER_S
{
    HI_S32 s32SNREn;    /*1bit*/
    HI_S32 s32YNr2dEn;    /*1bit*/
    HI_S32 s32CNr2dEn;    /*1bit*/
    HI_S32 s32ColorWeightEn;    /*1bit Enable Cb Cr Nr LUT*/
    HI_S32 s32MotionEdgeWeightEn;  /*1bit Enable Motion&Edge Nr LUT*/
    HI_S32 s32EdgePrefilterEn;    /*1bit*/
    HI_S32 s32MarketModeEn;     /*1bit*/
	HI_S32 s32MarketModeMux;     /*1bit*/
    HI_S32 s32TestModeEn;         /*1bit*/

    HI_S32 s32EdgeMaxRatio;     /*4bit   pixmean-ratio*/
    HI_S32 s32EdgeMinRatio;     /*4bit    pixmean-ratio*/
    HI_S32 s32EdgeOriRatio;     /*4bit    pixmean-ratio*/

    HI_S32 s32EdgeOriStrength;        /*4bit   newmaxpixdiff-edgestr*/
    HI_S32 s32EdgeMaxStrength;      /*4bit   newmaxpixdiff-edgestr*/
    HI_S32 s32EdgeMinStrength;       /*4bit   newmaxpixdiff-edgestr*/

    HI_S32 s32EdgeStrTh1;            /*10bit   newmaxpixdiff-edgestr    th1 < th2 < th3 */              
    HI_S32 s32EdgeStrTh2;             /*10bit   newmaxpixdiff-edgestr    th1 < th2 < th3 */ 
    HI_S32 s32EdgeStrTh3;              /*10bit   newmaxpixdiff-edgestr    th1 < th2 < th3 */ 

    HI_S32 s32EdgeStrK1;            /*6bit   newmaxpixdiff-edgestr*/
    HI_S32 s32EdgeStrK2;           /*6bit   newmaxpixdiff-edgestr*/
    HI_S32 s32EdgeStrK3;           /*6bit   newmaxpixdiff-edgestr*/

    HI_S32 s32EdgeMeanTh1;    /*10bit  pixmean-ratio    th1 < th2 < th3 < th4 < th5 < th6 < th7 < th8 */  
    HI_S32 s32EdgeMeanTh2;
    HI_S32 s32EdgeMeanTh3;
    HI_S32 s32EdgeMeanTh4;
    HI_S32 s32EdgeMeanTh5;
    HI_S32 s32EdgeMeanTh6;
    HI_S32 s32EdgeMeanTh7;
    HI_S32 s32EdgeMeanTh8;

    HI_S32 s32EdgeMeanK1;        /*6bit   pixmean-ratio*/
    HI_S32 s32EdgeMeanK2;
    HI_S32 s32EdgeMeanK3;
    HI_S32 s32EdgeMeanK4;
    HI_S32 s32EdgeMeanK5;
    HI_S32 s32EdgeMeanK6;
    HI_S32 s32EdgeMeanK7;
    HI_S32 s32EdgeMeanK8;

    HI_S32 s32Y2DWinWidth;          /*y�˲����ڿ�ȣ�5bit,          Ĭ��9             1,3,5,9,17*/ 
    /*y�˲����ڸ߶ȣ�4bit,         Ĭ��5 ,           1,3,5,9   
    ע�⣺�˴������ơ������ʽ��֧��9��(bufֻ�и���4��)     imgwidth����960ʱ�����϶�Ϊ����*/
    HI_S32 s32Y2DWinHeight;
    HI_S32 s32C2DWinWidth;           /*c�˲����ڿ�ȣ�4bit,           Ĭ��9                     1,3,5,9*/
    HI_S32 s32C2DWinHeight;          /*c�˲����ڸ߶ȣ�2bit,          Ĭ��3                     1,3*/

    HI_S32 s32YSNRStr;       /*y����ǿ�ȣ�8bit,     Ĭ��ֵ24*/
    HI_S32 s32CSNRStr;       /*c����ǿ�ȣ�8bit,     Ĭ��ֵ24*/
    HI_S32 s32YStrAdjust;     /*6bit,   �����л�ʱȥ���ǿ�ĳ̶ȣ�Ĭ��ֵ16*/
    HI_S32 s32CStrAdjust;     /*6bit,   �����л�ʱȥ���ǿ�ĳ̶ȣ�Ĭ��ֵ16*/

    HI_S32 s32StrOffset0;    /*2bit, �뵱ǰ�����Ϊ1�ĵ�Ľ�������λ����Ĭ��ֵ0*/
    HI_S32 s32StrOffset1;    /*2bit, �뵱ǰ�����Ϊ2�ĵ�Ľ�������λ����Ĭ��ֵ1*/
    HI_S32 s32StrOffset2;    /*2bit, �뵱ǰ�����Ϊ3~4�ĵ�Ľ�������λ����Ĭ��ֵ2*/
    HI_S32 s32StrOffset3;    /*2bit, �뵱ǰ�����Ϊ5~8�ĵ�Ľ�������λ����Ĭ��ֵ3*/

    HI_S32 s32SceneChangeTh;  /*4bit,    �����л�ָʾ���ޣ�Ĭ��ֵ7*/
	HI_S32 s32SceneChangeInfo;  /*4bit,    �����л���Ϣ*/
	HI_S32 s32SceneChangeEn;
	HI_S32 s32SceneChangeMode1En;
	HI_S32 s32SceneChangeMode2En;
	HI_S32 s32SceneChangeBldCore;
	HI_S32 s32SceneChangeBldK;

	HI_S32 s32PixMeanRatio1;   /*9bit   pixmean-ratioӳ��edgemeanth1��Ӧ��ratio*/
	HI_S32 s32PixMeanRatio2;
	HI_S32 s32PixMeanRatio3;
	HI_S32 s32PixMeanRatio4;
	HI_S32 s32PixMeanRatio5;
	HI_S32 s32PixMeanRatio6;
	HI_S32 s32PixMeanRatio7;
	HI_S32 s32PixMeanRatio8;

	HI_S32 s32EdgeStr1;    /*4bit   newmaxpixdiff-edgestrӳ��edgestrth1��Ӧ��edge*/
	HI_S32 s32EdgeStr2;
	HI_S32 s32EdgeStr3;
	

    HI_S32 s32TestColorCb;    /*10bit,  ����ģʽ�ı���ɫ*/
    HI_S32 s32TestColorCr;

    HI_U32 au32ColorBasedLUT[32];     /*32bit*/
    HI_U32 au32MotionEdgeLUT[32];    /*32bit*/
} SNR_PARAMETER_S;





typedef struct  hiNR_PARAMETER_S
{
    TNR_PARAMETER_S stTNrParameter;
    SNR_PARAMETER_S stSNrParameter;
} NR_PARAMETER_S;




/*SNR ��pixmean-ratioӳ������*/
typedef struct  hiSNR_PIXMEAN_2_RATIO_S
{
	HI_U8 u8EdgeMaxRatio;     /*4bit   pixmean-ratio*/
	HI_U8 u8EdgeMinRatio;     /*4bit    pixmean-ratio*/
	HI_U8 u8EdgeOriRatio;     /*4bit    pixmean-ratio*/
	HI_U8 u8Reserve;             /*reserve*/
	HI_U16 u16EdgeMeanTh[8];    /*10bit  pixmean-ratio    th1 < th2 < th3 < th4 < th5 < th6 < th7 < th8 */  
	HI_U8 u8EdgeMeanK[8];        /*6bit   pixmean-ratio*/
	HI_U16 u16PixMeanRatio[8];   /*9bit   pixmean-ratioӳ��edgemeanth1��Ӧ��ratio*/
} SNR_PIXMEAN_2_RATIO_S;

/*SNR ��pixdiff-edgestrӳ������*/
typedef struct  hiSNR_PIXDIFF_2_EDGESTR_S
{
	HI_U8 u8EdgeOriStrength;        /*4bit   newmaxpixdiff-edgestr*/
	HI_U8 u8EdgeMaxStrength;      /*4bit   newmaxpixdiff-edgestr*/
	HI_U8 u8EdgeMinStrength;       /*4bit   newmaxpixdiff-edgestr*/
	HI_U8 u8Reserve1;             /*reserve*/
	HI_U16 u16EdgeStrTh[3];            /*10bit   newmaxpixdiff-edgestr    th1 < th2 < th3 */              
	HI_U16 u16Reserve2;             /*reserve*/
	HI_U8 u8EdgeStrK[3];            /*6bit   newmaxpixdiff-edgestr*/
	HI_U8 u8Reserve3;             /*reserve*/
	HI_U8 u8EdgeStr[3];    /*4bit   newmaxpixdiff-edgestrӳ��edgestrth1��Ӧ��edge*/
	HI_U8 u8Reserve4;             /*reserve*/
} SNR_PIXDIFF_2_EDGESTR_S;



/*TNR ��ӳ������*/
typedef struct  hiTNR_MAPPING_S
{
	HI_S32 s32MappingMax;
	HI_S32 s32MappingMin;
	HI_S32 s32MappingR[5];   /*Result*/
	HI_S32 s32MappingT[6];   /*Threshhold*/
	HI_S32 s32MappingK[4];   /*Slope*/

} TNR_MAPPING_S;


//MotionResult
typedef struct
{
	HI_U32 u32GlobalMotion;
	HI_U32 u32AdjustGain;
}TNR_MOTION_RESULT_S;



/**
 \brief : Write Nr Parameter into the Register;
 \attention \n

 \param[in] pstNrPara

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_SetNRRegist(HI_U32 u32HandleNo, NR_PARAMETER_S * pstNrPara);

/**
 \brief :  Set Nr Strength;

 \param[in] s32NRStr

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_SetNRStr(HI_U32 u32HandleNo, HI_S32 s32NRStr);


/**
 \brief :  Enable or Disable Nr Module;

 \param[in] bNROnOff

 \retval ::HI_SUCCESS
 */
HI_S32 PQ_HAL_EnableNR(HI_U32 u32HandleNo, HI_BOOL bNROnOff);


/**
 \brief :  Enable or Disable TNr Module;

 \param[in] bNROnOff

 \retval ::HI_SUCCESS
 */
HI_S32 PQ_HAL_EnableTNR(HI_U32 u32HandleNo, HI_BOOL bNROnOff);


/**
 \brief :  Enable or Disable SNr Module;

 \param[in] bNROnOff

 \retval ::HI_SUCCESS
 */
HI_S32 PQ_HAL_EnableSNR(HI_U32 u32HandleNo, HI_BOOL bNROnOff);


/**
 \brief :  Enable or Disable Nr Demo Mode;

 \param[in] bNROnOff

 \retval ::HI_SUCCESS
 */
HI_S32 PQ_HAL_EnableNRDemo(HI_U32 u32HandleNo, HI_BOOL bNRDemoEn);



/**
 \brief :  Save the Nr Parameter in Middle Strength;

 \param[in] u32HandleNo

 \retval ::HI_SUCCESS
 */
HI_S32 PQ_HAL_SetNRMidStr(HI_U32 u32HandleNo);


/**
  \brief ����TNR��Global Motion �Ĵ�������
  \attention \n
 ��
 
  \param[in] u32HandleNo, pstMotionResult
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetTnrGMReg(HI_U32 u32HandleNo, TNR_MOTION_RESULT_S *pstMotionResult);

/**
 \brief ��ȡ�����˶���ϢProgress globa motion����״̬
 \attention \n
��

 \param[in] u32HandleNo

 \retval HI_BOOL:pglb����

 */
HI_BOOL PQ_HAL_GetProgressMotionEn(HI_U32 u32HandleNo);

/**
  \brief ����NR�Զ����ܿ���״̬����ȡglobal motion gain��ֵ
  \attention \n
	��NR�Զ����ܴ򿪣���VPSS_TNR_YMOTION_MAP_CTRL��ȡ
	��NR�Զ����ܹرգ���VPSS_TNR_CMOTION_MAP_CTRL��ȡ
  \param[in] bFlag NR�Զ����ܿ���״̬
			 u32HandleNo ��ʵ��ID��
  \param[out] pu32MotionGain ��������Gainֵ[0,255]
 
  \retval :HI_SUCCESS
 
  */
HI_S32 PQ_HAL_ReadTnrMotionGain(HI_U32 *pu32MotionGain, HI_U32 u32HandleNo, HI_BOOL bFlag);


/**
  \brief ����SNR��PIXMEAN-RATIO����
  \attention \n
 ��
 
  \param[in] pstSNR_Pixmean2Ratio
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetSnrPixmeanToRatio(HI_U32 u32HandleNo, SNR_PIXMEAN_2_RATIO_S *pstSNR_Pixmean2Ratio);



/**
  \brief ��ȡSNR��PIXMEAN-RATIO����
  \attention \n
 ��
 
  \param[out] pstSNR_Pixmean2Ratio
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_GetSnrPixmeanToRatio(HI_U32 u32HandleNo, SNR_PIXMEAN_2_RATIO_S *pstSNR_Pixmean2Ratio);




/**
  \brief ����SNR��PIXDIFF-EDGESTR����
  \attention \n
 ��
 
  \param[in] pstSNR_Pixdiff2Edgestr
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetSnrPixdiffToEdgestr(HI_U32 u32HandleNo, SNR_PIXDIFF_2_EDGESTR_S *pstSNR_Pixdiff2Edgestr);





/**
  \brief ��ȡSNR��PIXDIFF-EDGESTR����
  \attention \n
 ��
 
  \param[out] pstSNR_Pixdiff2Edgestr
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_GetSnrPixdiffToEdgestr(HI_U32 u32HandleNo, SNR_PIXDIFF_2_EDGESTR_S *pstSNR_Pixdiff2Edgestr);






/**
  \brief ����TNR��PixMean-Ratio For YMotion Detection����
  \attention \n
 ��
 
  \param[in] pstTNR_YMotionPixmeanRatio
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetTnrYMotionPixMeanRatio(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_YMotionPixmeanRatio);






/**
  \brief ��ȡTNR��PixMean-Ratio For YMotion Detection����
  \attention \n
 ��
 
  \param[in] pstTNR_YMotionPixmeanRatio
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_GetTnrYMotionPixMeanRatio(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_YMotionPixmeanRatio);






/**
  \brief ����TNR��PixMean-Ratio For CMotion Detection����
  \attention \n
 ��
 
  \param[in] pstTNR_CMotionPixmeanRatio
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetTnrCMotionPixMeanRatio(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_CMotionPixmeanRatio);





/**
  \brief ��ȡTNR��PixMean-Ratio For CMotion Detection����
  \attention \n
 ��
 
  \param[in] pstTNR_CMotionPixmeanRatio
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_GetTnrCMotionPixMeanRatio(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_CMotionPixmeanRatio);






/**
  \brief ����TNR��YMotionMapping����
  \attention \n
 ��
 
  \param[in] pstTNR_YMotionMapping
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetTnrYMotionMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_YMotionMapping);







/**
  \brief ��ȡTNR��YMotionMapping����
  \attention \n
 ��
 
  \param[in] pstTNR_YMotionMapping
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_GetTnrYMotionMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_YMotionMapping);









/**
  \brief ����TNR��CMotonMapping ����
  \attention \n
 ��
 
  \param[in] pstTNR_CMotionMapping
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetTnrCMotionMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_CMotionMapping);








/**
  \brief ��ȡTNR��CMotonMapping����
  \attention \n
 ��
 
  \param[in] pstTNR_CMotionMapping
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_GetTnrCMotionMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_CMotionMapping);






/**
  \brief ����TNR��Final Y Motion Mapping����
  \attention \n
 ��
 
  \param[in] pstTNR_FnlMotionYMapping
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetTnrFnlMotionYMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_FnlMotionYMapping);







/**
  \brief ��ȡTNR��Final Y Motion Mapping����
  \attention \n
 ��
 
  \param[in] pstTNR_FnlMotionYMapping
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_GetTnrFnlMotionYMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_FnlMotionYMapping);






/**
  \brief ����TNR��Final C Motion Mapping����
  \attention \n
 ��
 
  \param[in] pstTNR_FnlMotionCMapping
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_SetTnrFnlMotionCMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_FnlMotionCMapping);



/**
  \brief ��ȡTNR��Final C Motion Mapping����
  \attention \n
 ��
 
  \param[in] pstTNR_FnlMotionCMapping
 
  \retval ::HI_SUCCESS
 
  */

HI_S32 PQ_HAL_GetTnrFnlMotionCMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_FnlMotionCMapping);


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif

