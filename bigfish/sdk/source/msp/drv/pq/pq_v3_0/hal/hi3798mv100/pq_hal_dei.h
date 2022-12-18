/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_dei.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/20
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_DEI_H__
#define __PQ_HAL_DEI_H__

#include "hi_type.h"
#include "hi_drv_mmz.h"
#include "pq_hal_comm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


//add for 3798m_a
typedef struct
{
    HI_BOOL bMfMaxChr;     /*motion decision result for chroma: 0-chroma mf is statistic value; 1-chroma mf fixed to maximum value*/
    HI_BOOL bMfMaxLum;     /*motion decision result for luma: 0-luma mf is statistic value; 1-luma mf fixed to maximum value*/
    HI_BOOL bSceSdfMaxLum; /*SAD choice between SCE and SDF for luma: 0- minimum; 1-maximum*/
    HI_BOOL bRecMdEn;
    HI_BOOL bMtnIIrEn;
    HI_BOOL bFrmMtnSmthEn;
    HI_BOOL bRecmdFrmfldBldMd;
    HI_S32  s32MfOffsetChr;
} MAD_MTNCTRL_S;

typedef struct
{
    HI_S32  s32MinIntenVer;  /* 16 bit*/
    HI_S32  s32DirIntenVer;  /* 4  bit*/
    HI_S32  s32RangeScale;   /* 8  bit*/

    HI_S32  s32StrengthThd;  /* 16 bit*/
    HI_S32  s32DirThd;       /* 4  bit, direction choose threshold*/
    HI_S32  s32BcGain;       /* 7  bit, the weight value of check module, maximum value is 64 */

    HI_BOOL bHorEdgeEn;
    HI_BOOL bEdgeMd;
    HI_BOOL bMedBldEn;
} MAD_INTPCTRL_S;

typedef struct
{
    HI_S32 s32CkGain;      /*4 bit*/
    HI_S32 s32CkRangeGain; /*4 bit*/
    HI_S32 s32CkMaxRange;  /*8 bit*/
} MAD_CHECK_S;

typedef struct
{
    HI_S32 s32MultDir[15];   /* 6 bit*/
} MAD_DIRMULT_S;

typedef struct
{
    HI_BOOL bCcrEn;           /* cross color reduction enable: 0-off; 1-on */
    HI_S32  s32ChrMaOffset;   /* 10 bit, chroma motion offset compared with luma motion */
    HI_S32  s32NCcrDetMax;    /* 10 bit, Cross luma detection maximum value */
    HI_S32  s32NccrDetThd;    /* 10 bit, Cross luma detection threshold */
    HI_S32  s32SimlrMax;      /* 9  bit, Maximum value of similarity */
    HI_S32  s32SimlrThd;      /* 9  bit, Threshold of similarity */
    HI_S32  s32NCcrDetBld;    /* 14 bit, blending ratio of cross luma detection */
    HI_S32  s32XChrMax;       /* 10 bit, maximum change of chroma */
} MAD_CCRSCLR_S;

typedef struct
{
    HI_S32 s32IntpSclRat[15];    /*4 bit, strength ratio of each direction */
} MAD_INTPSCL_S;

/*MAD comb check module paras*/
typedef struct
{
    HI_BOOL bCombChkEn;        /* comb check enable */
    HI_S32  s32CombChkUpLmt;   /* 8 bit, comb check upper limit threshold */
    HI_S32  s32CombChkLowLmt;  /* 8 bit, comb check lower limit threshold */
    HI_S32  s32CombChkMinThdV; /* 8 bit, comb check minus vertical threshold */
    HI_S32  s32CombChkMinThdH; /* 8 bit, comb check minus horizontal threshold */
    HI_S32  s32CombChkMdThd;   /* 5 bit, comb check motion threshold */
    HI_S32  s32CombChkEdgeThd; /* 7 bit, comb check edge strength threshold */
} MAD_CombChk_S;

typedef struct
{
    HI_S32 s32JitGain;
    HI_S32 s32JitCoring;
} MAD_JITMTN_S;

typedef struct
{
    HI_S32 s32FldMtnGain;
    HI_S32 s32FldMtnCoring;
    HI_S32 s32FldMtnThdLow;
    HI_S32 s32FldMtnThdHigh;
    HI_S32 s32FldMtnCrvSlp;
} MAD_FLDMTN_S;

typedef struct
{
    HI_BOOL bHistMtnEn;
    HI_BOOL bHistMtnInfoWrtMd;
    HI_BOOL bHistMtnWrtMd;
    HI_BOOL bHistMtnUseMd;
    HI_BOOL bPreInfoEn;
    HI_BOOL bPpreInfoEn;
} MAD_HISTMTN_S;

typedef struct
{
    HI_S32 s32RecMdFrmMtnStp[2];
    HI_S32 s32RecMdFldMtnStp[2];
} MAD_RECMD_S;

typedef struct
{
    HI_S32 s32MtnDiffThd[6];
    HI_S32 s32MtnIirCrvSlp[4];
    HI_S32 s32MtnIirCrvRat[5];
    HI_S32 s32MtnIirCrvRatMin;
    HI_S32 s32MtnIirCrvRatMax;
} MAD_IIRMTNCRV_S;

typedef struct
{
    HI_S32 s32FrmMtnSmthThd[6];
    HI_S32 s32FrmMtnSmthSlp[4];
    HI_S32 s32FrmMtnSmthRat[5];
    HI_S32 s32FrmMtnSmthRatMin;
    HI_S32 s32FrmMtnSmthRatMax;
} MAD_FRMMTNSMTH_S;

typedef struct
{
    HI_S32 s32FrmFldBldThd[6];
    HI_S32 s32FrmFldBldSlp[4];
    HI_S32 s32FrmFldBldRat[5];
    HI_S32 s32FrmFldBldRatMin;
    HI_S32 s32FrmFldBldRatMax;
} MAD_FRMFLDBLEND_S;

typedef struct
{
    HI_BOOL bMorFltEn;
    HI_S32  s32MorFltSize;
    HI_S32  s32MorFltThd;
} MAD_MORFLT_S;

typedef struct
{
    HI_S32 s32MtnAdjGain;
    HI_S32 s32MtnAdjGainChr;
    HI_S32 s32MtnAdjCoring;
} MAD_MTNADJ_S;

typedef struct
{
    HI_S32 s32MtnThdSmall;
    HI_S32 s32MtnThdLarge;

    HI_S32 s32MtnThdMiddle0;
    HI_S32 s32MtnThdMiddle1;
} MAD_GLBMTNTHD_S;

typedef struct
{
    HI_S32 u32Die_cmmode;
    HI_S32 u32Die_lmmode;
    HI_S32 u32Die_out_sel_c;
    HI_S32 u32Die_out_sel_l;
} FMD_CTRL_S; //FMD Ctrl

typedef struct
{
    FMD_CTRL_S        stFmdCtrl;
    MAD_MTNCTRL_S     stMadMtnCtrl;
    MAD_INTPCTRL_S    stMadIntpCtrl;
    MAD_CHECK_S       stMadChk1;
    MAD_CHECK_S       stMadChk2;
    MAD_DIRMULT_S     stMadDirMult;
    MAD_CCRSCLR_S     stMadCcrScl;
    MAD_INTPSCL_S     stMadIntpScl;
    MAD_CombChk_S     stMadCombChk;
    MAD_JITMTN_S      stMadJitMtn;
    MAD_FLDMTN_S      stMadFldMtn;
    MAD_HISTMTN_S     stMadHistMtn;
    MAD_RECMD_S       stMadRecMd;
    MAD_IIRMTNCRV_S   stIirMtnCrv;
    MAD_FRMMTNSMTH_S  stFrmMtnSmth;
    MAD_FRMFLDBLEND_S stFrmFldBld;
    MAD_MORFLT_S      stMadMorFlt;
    MAD_MTNADJ_S      stMadMtnAdj;
    MAD_GLBMTNTHD_S   stMadGlbMtnThd;

    HI_U32  u32MadSTBufAddrR;
    HI_U32  u32MadSTBufAddrW;
    HI_U32  u32MadSTBufStride;
    HI_BOOL bMadMvInfoStp;    /* 0-normal update; 1-stop update infomation,don't write back motion informaion */

    HI_BOOL bIgblEn;          /* Interlance Global Motion Enable */
} DEI_MAD_COEF_S;


typedef struct
{
    MMZ_BUFFER_S stMBuf;
    HI_U32 u32MadMvAddr[3];
}ALG_MAD_MEM_S;


typedef struct {
    //input of logic
    HI_U32 SMALL_MOTION_THD;            /* input of logic, 10bit unsigend */
    HI_U32 LARGE_MOTION_THD;            /* input of logic, 10bit unsigend */
    //output of logic and input of software
    HI_U32 MOTION_HIST[32];             /* output of logic, 32bit unsigned */
    HI_U32 SMALL_MOTION_NUM;            /* output of logic, 32bit unsigned */
    HI_U32 SMALL_MOTION_SUM;            /* output of logic, 32bit unsigned */ 
    HI_U32 LARGE_MOTION_NUM;            /* output of logic, 32bit unsigned */ 
    HI_U32 LARGE_MOTION_SUM;            /* output of logic, 32bit unsigned */    
    HI_U32 MIDDL_MOTION_NUM;            /* output of logic, 32bit unsigned */
    HI_U32 MIDDL_MOTION_SUM;            /* output of logic, 32bit unsigned */
    //input of software
    HI_U16 GLOBAL_MOTION_EN;
    HI_U16 GLOBAL_MOTION_THD[6];        /* 8-bit unsigned */
    HI_U16 GLOBAL_MOTION_RATIO[5];      /* 8-bit unsigned, (2.6) */
    HI_S16 GLOBAL_MOTION_SLOPE[4];      /* 6-bit signed,   (3.3) */
    HI_U16 MAX_GLOBAL_MOTION_RATIO;     /* 8-bit unsigned, (2.6) */
    HI_U16 MIN_GLOBAL_MOTION_RATIO;     /* 8-bit unsigned, (2.6) */
}MotionHist_S;

typedef struct
{
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32HandleNo;
    S_VPSSWB_REGS_TYPE* pstMotionReg;
} MOTION_INPUT_S; //MotionInput_S


/**
 \brief 设置deinterlace模块寄存器初始化参数
 \attention \n

 \param[in]: &stDeiPara

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_SetDeiRegist(HI_U32 u32HandleNo, DEI_MAD_COEF_S* pstDeiPara);

/**
 \brief根据globalmotion 计算出的运动信息调整gain值
 \attention \n
无

 \param[in] u32HandleNo,u32AdjustGain

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_SetDeiAdjustGain(HI_U32 u32HandleNo, HI_U32 u32AdjustGain, HI_U32 u32GlobalMotion);

HI_S32 PQ_HAL_SetDeiParam(HI_U32 u32HandleNo, DEI_MAD_COEF_S* pstDeiPara);

HI_S32 PQ_HAL_GetMotionHistReg(MOTION_INPUT_S* pstMotionInput, MotionHist_S* pstMotionHist);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif


